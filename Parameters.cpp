/*
  ==============================================================================

    Parameters.cpp
    Created: 1 Aug 2025 5:56:37pm
    Author:  ersla

  ==============================================================================
*/

#include "Parameters.h"

template<typename T>
static void castParameter(juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& id, T& destination) {
    destination = dynamic_cast<T>(apvts.getParameter(id.getParamID()));
    jassert(destination); //parameter does not exist or wrong type
    
    //castParameter(apvts, mixParamID, mixParam); //does this go here??
    //castParameter(apvts, delayTimeParamID, delayTimeParam); 
}

static juce::String stringFromMilliseconds(float value, int) {
    if (value < 10.0f) {
        return juce::String(value, 2) + " ms";
    }
    else if (value < 100.0f) {
        return juce::String(value, 1) + " ms";
    }
    else if (value < 1000.0f) {
        return juce::String(int(value)) + " ms";
    }
    else {
        return juce::String(value * 0.001f, 2) + " s";
    }
}

static juce::String stringFromDecibels(float value, int) {
    return juce::String(value, 1) + " dB";
}

static juce::String stringFromPercent(float value, int) {
    return juce::String(int(value)) + " %";
}

Parameters::Parameters(juce::AudioProcessorValueTreeState& apvts) {
    castParameter(apvts, gainParamID, gainParam);
    castParameter(apvts, delayTimeParamID, delayTimeParam);
    castParameter(apvts, mixParamID, mixParam); //just added this line!!!!! not sure if need!
}

juce::AudioProcessorValueTreeState::ParameterLayout Parameters::createParameterLayout() {
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        gainParamID, //unique identifier
        "Output Gain", //name of parameter
        juce::NormalisableRange<float> {-12.0f, 12.0f}, //range of parameter
        0.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromDecibels))); //default value

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        delayTimeParamID,
        "Delay Time",
        juce::NormalisableRange<float> { minDelayTime, maxDelayTime, 0.001f, 0.25f}, //0.001f is the slider step size (in ms), 0.25f is the skew factor (smaller number means more emhasis lower numbers get on the slider
        100.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromMilliseconds)));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        mixParamID,
        "Mix",
        juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f), //range of parameter is 0.0 to 100.0 in steps of 1.0
        100.0f, //default setting (100%)
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)

    ));

    return layout;
}

void Parameters::update() noexcept {
    gainSmoother.setTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));

    targetDelayTime = delayTimeParam->get();
    if (delayTime == 0.0f) {
        delayTime = targetDelayTime;
    }

    mixSmoother.setTargetValue(mixParam->get() * 0.01f); //set smoothers target value
}

void Parameters::prepareToPlay(double sampleRate) noexcept {
    double duration = 0.02;
    gainSmoother.reset(sampleRate, duration);

    coeff = 1.0f - std::exp(-1.0f / (0.2f * float(sampleRate))); //filter coefficient

    mixSmoother.reset(sampleRate, duration); //tell smoother about sample rate
}

void Parameters::reset() noexcept {
    gain = 0.0f;
    gainSmoother.setCurrentAndTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));

    delayTime = 0.0f;

    //set smoothers current and target values
    mix = 1.0f;
    mixSmoother.setCurrentAndTargetValue(mixParam->get() * 0.01f);
}

void Parameters::smoothen() noexcept {
    gain = gainSmoother.getNextValue();

    delayTime += (targetDelayTime - delayTime) * coeff;

    mix = mixSmoother.getNextValue(); //read value from smoother and put it in the mix variable
}




