/*
    +====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====++++++++++
 
        Hard Clip Distortion
        MJM
        November 14, 2018
 
    +====+====+====+====+====+====+====+====+====+====+====+====+====+====+====+====++++++++++
 */


#include "PluginProcessor.h"
#include "PluginEditor.h"

//==================================================================================++++++++++
HardClipDistortionv1AudioProcessorEditor::HardClipDistortionv1AudioProcessorEditor
                                         (HardClipDistortionv1AudioProcessor& p) :
                                          AudioProcessorEditor (&p),
                                          processor (p)
{
    setSize (400, 300);
    
    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(Slider::LinearVertical);
    gainSlider.setRange(0.0, 1.0, 0.01);
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 75, 20);
    gainSlider.addListener(this);
    
    addAndMakeVisible(hardClipSlider);
    hardClipSlider.setSliderStyle(Slider::LinearVertical);
    hardClipSlider.setRange(0.0, 1.0, 0.01);
    hardClipSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 75, 20);
    hardClipSlider.addListener(this);
    
    addAndMakeVisible(gainLabel);
    gainLabel.setText("Gain", dontSendNotification);
    gainLabel.attachToComponent(&gainSlider, false);
    
    addAndMakeVisible(driveLabel);
    driveLabel.setText("Drive", dontSendNotification);
    driveLabel.attachToComponent(&hardClipSlider, false);
    
    startTimer(50);
}

//==================================================================================++++++++++
HardClipDistortionv1AudioProcessorEditor::~HardClipDistortionv1AudioProcessorEditor() {}

//==================================================================================++++++++++
void HardClipDistortionv1AudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

//==================================================================================++++++++++
void HardClipDistortionv1AudioProcessorEditor::resized()
{
    gainSlider.setBounds    (35,               (getHeight() * 0.5) - 75, 150, 150);
    hardClipSlider.setBounds(getWidth() - 185, (getHeight() * 0.5) - 75, 150, 150);
}

//==================================================================================++++++++++
void HardClipDistortionv1AudioProcessorEditor::sliderValueChanged(Slider* sliderThatChanged)
{
    if (sliderThatChanged == &gainSlider)
    {
        processor.gainParam->beginChangeGesture();
        processor.gainParam->setValueNotifyingHost(gainSlider.getValue());
        processor.gainParam->endChangeGesture();
    }
    
    if (sliderThatChanged == &hardClipSlider)
    {
        processor.hardClipParam->beginChangeGesture();
        processor.hardClipParam->setValueNotifyingHost(hardClipSlider.getValue());
        processor.hardClipParam->endChangeGesture();
    }
}

//==================================================================================++++++++++
void HardClipDistortionv1AudioProcessorEditor::timerCallback()
{
    gainSlider.setValue(processor.gainParam->get(), dontSendNotification);
    //auto clipValue = processor.hardClipParam->get(); // Get the value
    hardClipSlider.setValue(processor.hardClipParam->get(), dontSendNotification);
}
