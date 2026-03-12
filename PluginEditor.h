/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Testing123AudioProcessorEditor  : public juce::AudioProcessorEditor,
                                        public juce::Slider::Listener
{
public:
    Testing123AudioProcessorEditor (Testing123AudioProcessor&);
    ~Testing123AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (juce::Slider* slider) override;

private:

    juce::Slider mGainSlider;
    juce::Slider mPitchSlider;
    Testing123AudioProcessor& audioProcessor;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Testing123AudioProcessorEditor)
};

