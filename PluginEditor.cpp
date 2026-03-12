/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Testing123AudioProcessorEditor::Testing123AudioProcessorEditor (Testing123AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    mGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mGainSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 50, 20);
    mGainSlider.setRange(0.0f, 1.0f, 0.01f);
    mGainSlider.setValue(0.5f);
    mGainSlider.addListener(this);
    addAndMakeVisible(mGainSlider);

    mPitchSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mPitchSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 50, 20);
    mPitchSlider.setRange (-12.0, 12.0);
    mPitchSlider.setValue(0.0);
    mPitchSlider.addListener(this);
    addAndMakeVisible(mPitchSlider);

    
    setSize (200, 300);
}

Testing123AudioProcessorEditor::~Testing123AudioProcessorEditor()
{
}

//==============================================================================
void Testing123AudioProcessorEditor::paint (juce::Graphics& g)
{

    g.fillAll(juce::Colours::black);
    
}

void Testing123AudioProcessorEditor::resized()
{
    int sliderWidth = 100;
    int sliderHeight = 150;
    int margin = 20; // Adjust the margin between sliders as needed
    
    mPitchSlider.setBounds(getWidth() / 2 - sliderWidth - margin / 2, getHeight() / 2 - sliderHeight / 2, sliderWidth, sliderHeight);
    mGainSlider.setBounds(getWidth() / 2 + margin / 2, getHeight() / 2 - sliderHeight / 2, sliderWidth, sliderHeight);
}

void Testing123AudioProcessorEditor::sliderValueChanged (juce::Slider* slider) {
    if (slider == &mGainSlider) {
        audioProcessor.mGain = mGainSlider.getValue();
    }
    else if (slider == &mPitchSlider) {
        audioProcessor.mPitch = mPitchSlider.getValue();
    }
}

