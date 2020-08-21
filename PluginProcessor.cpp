/*
    +====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====++++++++++++

        Hard Clip Distortion
        MJM
        November 14, 2018

    +====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====++++++++++++
*/


#include "PluginProcessor.h"
#include "PluginEditor.h"

//==================================================================================++++++++++
HardClipDistortionv1AudioProcessor::HardClipDistortionv1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
                                   : AudioProcessor (BusesProperties()
                                     #if ! JucePlugin_IsMidiEffect
                                     #if ! JucePlugin_IsSynth
                                     .withInput     ("Input",  AudioChannelSet::stereo(), true)
                                     #endif
                                     .withOutput    ("Output", AudioChannelSet::stereo(), true)
                                     #endif
                                    )
                                     #endif
{
    NormalisableRange<float> gainRange(0.0, 1.0, 0.1, 1.0);
    addParameter(gainParam = new AudioParameterFloat("gainParam", "Gain", gainRange, 1.0));
    
    NormalisableRange<float> driveRange(0.0, 1.0, 0.1, 1.0);
    addParameter(hardClipParam = new AudioParameterFloat("hardClipParam", "Drive", driveRange, 1.0));
}

//==================================================================================++++++++++
HardClipDistortionv1AudioProcessor::~HardClipDistortionv1AudioProcessor() {}

//==================================================================================++++++++++
const String HardClipDistortionv1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

//==================================================================================++++++++++
bool HardClipDistortionv1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

//==================================================================================++++++++++
bool HardClipDistortionv1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

//==================================================================================++++++++++
bool HardClipDistortionv1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

//==================================================================================++++++++++
double HardClipDistortionv1AudioProcessor::getTailLengthSeconds() const { return 0.0; }

//==================================================================================++++++++++
int HardClipDistortionv1AudioProcessor::getNumPrograms() { return 1; }

//==================================================================================++++++++++
int HardClipDistortionv1AudioProcessor::getCurrentProgram() { return 0; }

//==================================================================================++++++++++
void HardClipDistortionv1AudioProcessor::setCurrentProgram (int index) {}

//==================================================================================++++++++++
const String HardClipDistortionv1AudioProcessor::getProgramName (int index){ return {}; }

//==================================================================================++++++++++
void HardClipDistortionv1AudioProcessor::changeProgramName (int index, const String& newName) {}

//==================================================================================++++++++++
void HardClipDistortionv1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {}

//==================================================================================++++++++++
void HardClipDistortionv1AudioProcessor::releaseResources() {}

//==================================================================================++++++++++
#ifndef JucePlugin_PreferredChannelConfigurations
bool HardClipDistortionv1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

//==================================================================================++++++++++
void HardClipDistortionv1AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData[sample] *= hardClipParam->get();
            channelData[sample] *= 4.0; // 0 - 4 range
            channelData[sample] += 1.0; // 1 - 5 range
            
            if      (channelData[sample] >  1) channelData[sample] =  1;
            else if (channelData[sample] < -1) channelData[sample] = -1;
            
            channelData[sample] *= (gainParam->get());
        }
    }
}

//==================================================================================++++++++++
bool HardClipDistortionv1AudioProcessor::hasEditor() const { return true; }

//==================================================================================++++++++++
AudioProcessorEditor* HardClipDistortionv1AudioProcessor::createEditor()
{
    return new HardClipDistortionv1AudioProcessorEditor (*this);
}

//==================================================================================++++++++++
void HardClipDistortionv1AudioProcessor::getStateInformation (MemoryBlock& destData) {}

//==================================================================================++++++++++
void HardClipDistortionv1AudioProcessor::setStateInformation (const void* data, int sizeInBytes) {}

//==================================================================================++++++++++
AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new HardClipDistortionv1AudioProcessor(); }
