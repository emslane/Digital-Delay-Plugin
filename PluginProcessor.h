/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Parameters.h"


//==============================================================================
/**
*/
class DelayAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    DelayAudioProcessor(); //constructor (for the host to load the plugin into the computers memory)
    ~DelayAudioProcessor() override; //destructor (remove from computers memory (such as when removed from a track))

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override; //member function for when wants to start playing audio (I will use to reserve enough memory to store 5s of sound)
    void releaseResources() override; //for when host stops playing audio (plugin can free un-needed resources)

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override; //where dsp happens!

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts{
        *this, nullptr, "Parameters", Parameters::createParameterLayout()
    };

private:
    //==============================================================================

    /*juce::AudioProcessorValueTreeState apvts{
        *this, nullptr, "Parameters", Parameters::createParameterLayout()
    };*/

    Parameters params;

    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLine; //juce::dsp::DelayLine is a class template, and needs to know the data type of the samples, and how to do the interpolation for delay lengths that fall in between samples

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayAudioProcessor)
};
