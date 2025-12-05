/*
  ==============================================================================

    RotaryKnob.cpp
    Created: 29 Nov 2025 2:20:58pm
    Author:  ersla

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RotaryKnob.h"
#include "LookAndFeel.h"

//==============================================================================
RotaryKnob::RotaryKnob(const juce::String& text,
                       juce::AudioProcessorValueTreeState& apvts,
                       const juce::ParameterID& parameterID) :
    attachment(apvts, parameterID.getParamID(), slider)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    //configure slider object to be rotary knob w/ text below the slider
    //rotaryhorizontalverticaldrag - round and responds to hor and vert mouse movements but not circular motion
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 16); //knob is 70x70 pix, txt box 16 pix high
    slider.setBounds(0, 0, 70, 86); //70 wide by (70+16)=86 high
    //above line placed slider at (0,0), changed in resized
    addAndMakeVisible(slider); //adds slider to editor, so drawn when editor painted (makes slider child component of the editor?)

    label.setText(text, juce::NotificationType::dontSendNotification); //sets text to text on label, 
    label.setJustificationType(juce::Justification::horizontallyCentred);
    label.setBorderSize(juce::BorderSize<int>{0, 0, 2, 0}); //puts extra 2 pixels of space between between bottom of label and top of knob
    label.attachToComponent(&slider, false); //will automatically attach self to top  of slider component
    addAndMakeVisible(label); //add label component to editor

    setLookAndFeel(RotaryKnobLookAndFeel::get());

    setSize(70, 110);

}

RotaryKnob::~RotaryKnob()
{
}

//void RotaryKnob::paint (juce::Graphics& g)
//{
//    /* This demo code just fills the component's background and
//       draws some placeholder text to get you started.
//
//       You should replace everything in this method with your own
//       drawing code..
//    */
//
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
//
//    g.setColour (juce::Colours::grey);
//    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
//
//    g.setColour (juce::Colours::white);
//    g.setFont (juce::FontOptions (14.0f));
//    g.drawText ("RotaryKnob", getLocalBounds(),
//                juce::Justification::centred, true);   // draw some placeholder text
//}

void RotaryKnob::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    slider.setTopLeftPosition(0, 24);
}
