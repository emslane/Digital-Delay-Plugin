/*
  ==============================================================================

    LookAndFeel.cpp
    Created: 4 Dec 2025 10:10:35pm
    Author:  ersla

  ==============================================================================
*/

#include "LookAndFeel.h"

const juce::Typeface::Ptr Fonts::typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::LatoMedium_ttf, BinaryData::LatoMedium_ttfSize); //creates typeface variable

juce::Font Fonts::getFont(float height) {
    return juce::Font(typeface).withHeight(height);
}

juce::Font RotaryKnobLookAndFeel::getLabelFont([[mayble_unused]] juce::Label& label) {
    return Fonts::getFont();
} //if havibg issues read end of pg 261

RotaryKnobLookAndFeel::RotaryKnobLookAndFeel() { //constructor, changes the colours used to draw the labels in the rotary knob
    setColour(juce::Label::textColourId, Colours::Knob::label); //label that goes above the knob
    setColour(juce::Slider::textBoxTextColourId, Colours::Knob::label); //textbox below the knob
    setColour(juce::Slider::rotarySliderFillColourId, Colours::Knob::trackActive); //just added this
}

MainLookAndFeel::MainLookAndFeel() {
    setColour(juce::GroupComponent::textColourId, Colours::Group::label);
    setColour(juce::GroupComponent::outlineColourId, Colours::Group::outline);
}

juce::Font MainLookAndFeel::getLabelFont([[maybe_unused]] juce::Label& label) {
    return Fonts::getFont();
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

    //arc around the outside of the knob
    auto center = bounds.getCentre();
    auto radius = bounds.getWidth() / 2.0f;
    auto lineWidth = 3.0f;
    auto arcRadius = radius - lineWidth / 2.0f;

    juce::Path backgroundArc; //creates juce::Path object that describes an arc portion of the circle
    backgroundArc.addCentredArc(center.x, center.y, arcRadius, arcRadius,
                                0.0f, rotaryStartAngle, rotaryEndAngle, true);

    auto strokeType = juce::PathStrokeType(lineWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded);
    g.setColour(Colours::Knob::trackBackground);
    g.strokePath(backgroundArc, strokeType); //only draw the outline instead of filling the shape

    //drawing the dial
    auto dialRadius = innerRect.getHeight() / 2.0f - lineWidth; // - lineWidth is so the dial doesnt extend all the way too the end
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    //trig on pg 250
    juce::Point<float> dialStart(center.x + 10.0f * std::sin(toAngle), center.y - 10.0f * std::cos(toAngle)); //+- 10 is so the dial doesnt start at the center of the circle
    juce::Point<float> dialEnd(center.x + dialRadius * std::sin(toAngle),
                               center.y - dialRadius * std::cos(toAngle));

    //new path describing the line between the dialStart and dialEnd points
    juce::Path dialPath;
    dialPath.startNewSubPath(dialStart);
    dialPath.lineTo(dialEnd);
    g.setColour(Colours::Knob::dial);
    g.strokePath(dialPath, strokeType);

    //add colour to the arc
    if (slider.isEnabled()) { //if slider is disabled then dont colour any of track
        float fromAngle = rotaryStartAngle;
        if (slider.getProperties()["drawFromMiddle"]) {
            fromAngle += (rotaryEndAngle - rotaryStartAngle) / 2.0f;
        }
        juce::Path valueArc;
        valueArc.addCentredArc(center.x, center.y, arcRadius, arcRadius, 0.0f, fromAngle, toAngle, true);

        g.setColour(slider.findColour(juce::Slider::rotarySliderFillColourId));
        g.strokePath(valueArc, strokeType);
    }
}
