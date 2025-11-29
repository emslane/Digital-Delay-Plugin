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
    addAndMakeVisible(gainKnob);

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
    gainKnob.setTopLeftPosition(215, 120); //first num is x coord, second num is y coord
}
