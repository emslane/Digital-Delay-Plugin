/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
//constructor:
DelayAudioProcessorEditor::DelayAudioProcessorEditor (DelayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //configure slider object to be rotary knob w/ text below the slider
    //rotaryhorizontalverticaldrag - round and responds to hor and vert mouse movements but not circular motion
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 16); //knob is 70x70 pix, txt box 16 pix high
    slider.setBounds(0, 0, 70, 86); //70 wide by (70+16)=86 high
    //above line placed slider at (0,0), changed in resized
    addAndMakeVisible(slider); //adds slider to editor, so drawn when editor painted (makes slider child component of the editor?)

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 330); //sets dimensions of editor window
}

DelayAudioProcessorEditor::~DelayAudioProcessorEditor()
{
}

//==============================================================================
// ************og version edited one below************
//void DelayAudioProcessorEditor::paint (juce::Graphics& g)
//{
//    // (Our component is opaque, so we must completely fill the background with a solid colour)
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
//
//    g.setColour (juce::Colours::white);
//    g.setFont (juce::FontOptions (15.0f));
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
//}

void DelayAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    /*g.fillAll(juce::Colours::beige);

    g.setColour(juce::Colours::darkseagreen);
    g.setFont(juce::FontOptions(15.0f));
    g.drawFittedText("Wowwww look at how cooooolll!!!!!!!", getLocalBounds(), juce::Justification::centred, 1);*/

    g.fillAll(juce::Colours::darkgrey);
}

void DelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
