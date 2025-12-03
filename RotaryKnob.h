/*
  ==============================================================================

    RotaryKnob.h
    Created: 29 Nov 2025 2:20:58pm
    Author:  ersla

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class RotaryKnob  : public juce::Component
{
public:
    RotaryKnob(const juce::String& text,
               juce::AudioProcessorValueTreeState& apvts,
               const juce::ParameterID& parameterID); //String& text for the labels for the knob ex gain
    ~RotaryKnob() override;

    juce::Slider slider;
    juce::Label label;

    juce::AudioProcessorValueTreeState::SliderAttachment attachment;

    //void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RotaryKnob)
};
