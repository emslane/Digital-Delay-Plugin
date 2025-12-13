/*
  ==============================================================================

    LookAndFeel.h
    Created: 4 Dec 2025 10:10:35pm
    Author:  ersla

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace Colours {
    const juce::Colour background{ 245, 240, 235 };
    const juce::Colour header{ 40, 40, 40 };

    namespace Knob {
        const juce::Colour trackBackground{ 205, 200, 195 }; //juce::Colour class lets you define your own colours
        const juce::Colour trackActive{ 177, 101, 135 }; //takes values for rgb, from 0 to 255
        const juce::Colour outline{ 255, 250, 245 };
        const juce::Colour gradientTop{ 250, 245, 240 };
        const juce::Colour gradientBottom{ 240, 235, 230 };
        const juce::Colour dial{ 100, 100, 100 };
        const juce::Colour dropShadow{ 195, 190, 185 };
        const juce::Colour label{ 80, 80, 80 };
        const juce::Colour textBoxBackground{ 80, 80, 80 };
        const juce::Colour value{ 240, 240, 240 };
        const juce::Colour caret{ 255, 255, 255 };
    }

    namespace Group {
        const juce::Colour label{ 160, 155, 150 };
        const juce::Colour outline{ 235, 230, 225 };
    }
}

class Fonts {
public:
    static juce::Font getFont(float height = 16.0f); //static means we dont need to create an instance of Fonts in order to use it

private:
    static const juce::Typeface::Ptr typeface;

    Fonts() = delete; //tells compiler that class Fonts does not have a constructor
};

class RotaryKnobLookAndFeel : public juce::LookAndFeel_V4 { //class based on juce::LookAndFeel_V4 class (greyish boring looking one)
public:
    RotaryKnobLookAndFeel(); //constructor (takes no arguments)

    static RotaryKnobLookAndFeel* get() { //lets us use RotaryKnobLookAndFeel from anywhere in the code instead of constructing a new instance each time??
        static RotaryKnobLookAndFeel instance;
        return &instance;
    }

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, //function that will paint the knob, called from juce::Slider's paint function
                          float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                          juce::Slider& slider) override; //overide cuz already have drawRotarySlider in base class (LookAndFeel_V4)

    juce::Font getLabelFont(juce::Label&) override;

private:
    juce::DropShadow dropShadow{ Colours::Knob::dropShadow, 6, {0, 3} }; //takes the colour, radius, offset (0 pix hor 3 pix ver)

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryKnobLookAndFeel) //macro that makes sure can not be copied and does not create memory leaks
};

class MainLookAndFeel : public juce::LookAndFeel_V4 {
public:
    MainLookAndFeel();

    juce::Font getLabelFont(juce::Label&) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainLookAndFeel)
};