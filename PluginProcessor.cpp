/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Testing123AudioProcessor::Testing123AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

Testing123AudioProcessor::~Testing123AudioProcessor()
{
}

//==============================================================================
const juce::String Testing123AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Testing123AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Testing123AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Testing123AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Testing123AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Testing123AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Testing123AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Testing123AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Testing123AudioProcessor::getProgramName (int index)
{
    return {};
}

void Testing123AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Testing123AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Testing123AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Testing123AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif


void Testing123AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    // Apply gain
    buffer.applyGain(mGain);

    // Calculate the pitch shift ratio
    float pitchRatio = pow(2.0f, mPitch / 12.0f); // Assuming pitch is in semitones

    // Iterate over channels
    for (int channel = 0; channel < getTotalNumInputChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        // Create temporary buffer for pitch shifting
        juce::AudioBuffer<float> tempBuffer(buffer.getNumChannels(), buffer.getNumSamples());
        tempBuffer.clear();

        // Apply pitch shifting algorithm
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            // Calculate the index for the original sample
            float index = sample / pitchRatio;
            int indexBefore = static_cast<int>(index);
            int indexAfter = indexBefore + 1;

            // Perform linear interpolation
            if (indexAfter < buffer.getNumSamples())
            {
                float fraction = index - indexBefore;
                float interpolatedSample = (1.0f - fraction) * channelData[indexBefore] +
                                           fraction * channelData[indexAfter];
                tempBuffer.setSample(channel, sample, interpolatedSample);
            }
        }

        // Copy the pitch-shifted data back to the original buffer
        buffer.copyFrom(channel, 0, tempBuffer, 0, 0, buffer.getNumSamples());
    }
}

//==============================================================================
bool Testing123AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Testing123AudioProcessor::createEditor()
{
    return new Testing123AudioProcessorEditor (*this);
}

//==============================================================================
void Testing123AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Testing123AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Testing123AudioProcessor();
}

