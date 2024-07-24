/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 60);
    
    // 2a. pointer to audioparam in audioprocessor
    auto& processorParams = audioProcessor.getParameters();
    
    // 2b. set attributes of slider
    mVolumeSlider.setBounds(60, 0, 250, 24); // x, y, width, height (in pixels)
    mVolumeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    mVolumeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 50, 30); // read0nly, w, h
    mVolumeSlider.setTextValueSuffix ("dB");
    
    BalanceSlider.setBounds(60, 24, 250, 24);
    BalanceSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    BalanceSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 50, 30);
    
    // 2c. set range of the slider to range of the audio param
    // first get a pointer to param object
    juce::AudioParameterFloat* procVParam =
        (juce::AudioParameterFloat*)processorParams.getUnchecked(0);
    mVolumeSlider.setRange(procVParam->range.start, procVParam->range.end);
    mVolumeSlider.setValue(*procVParam);
    
    juce::AudioParameterFloat* procBParam =
        (juce::AudioParameterFloat*)processorParams.getUnchecked(1);
    BalanceSlider.setRange(procBParam->range.start, procBParam->range.end);
    BalanceSlider.setValue(*procBParam);
    
    // 7. set ProcessorEditor to be a listener for our slider
    mVolumeSlider.addListener(this);
    BalanceSlider.addListener(this);
    
    // 3. add the slider
    addAndMakeVisible(mVolumeSlider);
    addAndMakeVisible(BalanceSlider);
    
    // adding labels
    addAndMakeVisible(mVolumeLabel);
    mVolumeLabel.setText("Volume", juce::dontSendNotification);
    mVolumeLabel.attachToComponent(&mVolumeSlider, true);  // attaches label to slider on the left
    
    addAndMakeVisible(BalanceLabel);
    BalanceLabel.setText("Balance", juce::dontSendNotification);
    BalanceLabel.attachToComponent(&BalanceSlider, true);  // attaches label to slider on the left
    
    // smiley face :)
    // I was going to add a smiley face but I worked on this section of code for like an hour and it still didn't work but know that the sentiment was there.
    /*
    addAndMakeVisible(smileyFace);
    smileyFace.setText(":)", juce::dontSendNotification);
    smileyFace.setJustificationType(juce::Justification::centredRight);
    smileyFace.setTransform(juce::AffineTransform::rotation(juce::MathConstants<float>::halfPi, .5 * getHeight(), .5 * getWidth()));
    smileyFace.attachToComponent(&mVolumeSlider, false);
    */
    
    
    

    
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

// 6. this will get called when any slider is changed
void NewProjectAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    // a. will point to audioParams in the AudioProcessor
    auto& proccessorParams = processor.getParameters();
    
    // b. compare pointer to slider that was changed w/ address of our slider
    if (slider == &mVolumeSlider)
    {
        // c. get a pointer to the first param in the processor
        juce::AudioParameterFloat* mGainParam = (juce::AudioParameterFloat*)proccessorParams.getUnchecked(0);
        
        // d. use value from slider to set param in processor
        float sliderValue = mVolumeSlider.getValue();
        *mGainParam = sliderValue;     // set the param
        
        
        // e. we can use DBG() for simple print debugging
        DBG("Volume Slider Changed to " << sliderValue);
    }
    if (slider == &BalanceSlider)
    {
        // c. get a pointer to the second param in the processor
        juce::AudioParameterFloat* BalanceParam = (juce::AudioParameterFloat*)proccessorParams.getUnchecked(1);
        
        // d. use value from slider to set param in processor
        float sliderValue = BalanceSlider.getValue();
        *BalanceParam = sliderValue;     // set the param
        
        
        // e. we can use DBG() for simple print debugging
        DBG("Balance Slider Changed to " << sliderValue);
    }
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
}
