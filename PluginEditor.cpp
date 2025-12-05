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
    //addAndMakeVisible(gainKnob);
    //addAndMakeVisible(mixKnob);
    //addAndMakeVisible(delayTimeKnob);

    delayGroup.setText("Delay");
    delayGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
    delayGroup.addAndMakeVisible(delayTimeKnob);
    addAndMakeVisible(delayGroup);

    feedbackGroup.setText("Feedback");
    feedbackGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
    addAndMakeVisible(feedbackGroup);

    outputGroup.setText("Output");
    outputGroup.setTextLabelPosition(juce::Justification::horizontallyCentred);
    outputGroup.addAndMakeVisible(gainKnob);
    outputGroup.addAndMakeVisible(mixKnob);
    addAndMakeVisible(outputGroup);

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

    g.fillAll(Colours::background);
}

void DelayAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();

    int y = 10;
    int height = bounds.getHeight() - 20;

    //position the groups
    delayGroup.setBounds(10, y, 110, height); //set bounds takes 4 inputs: x, y, width, and height

    outputGroup.setBounds(bounds.getWidth() - 160, y, 150, height);

    feedbackGroup.setBounds(delayGroup.getRight() + 10, y, outputGroup.getX() - delayGroup.getRight() - 20, height);

    //position the knobs inside the groups
    delayTimeKnob.setTopLeftPosition(20, 20); 
    mixKnob.setTopLeftPosition(20, 20);
    gainKnob.setTopLeftPosition(mixKnob.getX(), mixKnob.getBottom() + 10);
}
