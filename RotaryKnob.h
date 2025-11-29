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
    RotaryKnob();
    ~RotaryKnob() override;

    juce::Slider slider;
    juce::Label label;

    //void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RotaryKnob)
};
