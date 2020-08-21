/*
    +====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====++++++++++
 
        Hard Clip Distortion
        MJM
        November 14, 2018
 
    +====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====++++++++++
 */


#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class HardClipDistortionv1AudioProcessorEditor : public AudioProcessorEditor,
                                                 public Slider::Listener,
                                                 public Timer
{
public:
    HardClipDistortionv1AudioProcessorEditor(HardClipDistortionv1AudioProcessor&);
   ~HardClipDistortionv1AudioProcessorEditor();

    void paint              (Graphics&)                 override;
    void resized            ()                          override;
    void sliderValueChanged (Slider* sliderThatChanged) override;
    void timerCallback      ()                          override;
    
protected:
    

private:
    HardClipDistortionv1AudioProcessor& processor;
    
    Slider hardClipSlider, gainSlider;
    Label  driveLabel,     gainLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HardClipDistortionv1AudioProcessorEditor)
};
