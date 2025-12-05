/*
  ==============================================================================

    LookAndFeel.cpp
    Created: 4 Dec 2025 10:10:35pm
    Author:  ersla

  ==============================================================================
*/

#include "LookAndFeel.h"

RotaryKnobLookAndFeel::RotaryKnobLookAndFeel() { //constructor, changes the colours used to draw the labels in the rotary knob
    setColour(juce::Label::textColourId, Colours::Knob::label); //label that goes above the knob
    setColour(juce::Slider::textBoxTextColourId, Colours::Knob::label); //textbox below the knob
}

//good image of all parameters below on pg 243
void RotaryKnobLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, //juce::Graphics object is known as the graphics context, x,y,width,height are the bounds
                                             [[maybe_unused]] int height, float sliderPos, //sliderPos: current value of the slider as a proportion of its length (value between 0 and 1), maybe unused lets compiler know it isnt a mistake if we dont use it
                                             float rotaryStartAngle, float rotaryEndAngle, //knob starting and ending angle in radians
                                             juce::Slider& slider) { //slider object that im currently drawing
    auto bounds = juce::Rectangle<int>(x, y, width, width).toFloat(); //height also uses width? .toFloat turns the rectangle into type juce::Rectangel<float>
    auto knobRect = bounds.reduced(10.0f, 10.0f); // .reduced subtracts 10 pixels from each side of the rectangle to inset it inside the components bounds
    
    //for drop shadow (add before circle so the circle ends up on top)
    auto path = juce::Path(); //path is a series of points that are connected to create a certain shape (look into "path" in graphics terminology)
    path.addEllipse(knobRect);
    dropShadow.drawForPath(g, path);

    g.setColour(Colours::Knob::outline); //set current colour to Colours::KnobL::outline
    g.fillEllipse(knobRect); //draw filled circle inside the reduced rectangle

    //gradient inside the circle
    auto innerRect = knobRect.reduced(2.0f, 2.0f); //subtracts 2 pix from the square containing the knob
    auto gradient = juce::ColourGradient(Colours::Knob::gradientTop, 0.0f, innerRect.getY(),
                                         Colours::Knob::gradientBottom, 0.0f, innerRect.getBottom(),
                                         false); //transitions from COlours::Knob::gradientTop to Colours::Knob::gradientBottom
    g.setGradientFill(gradient); //tells the graphics context that from now on it should use this gradient to fill shapes instead of the colour previously set with g.setColour
    g.fillEllipse(innerRect); //draws the circle again but 2 pix smaller so theres a white outline
}
