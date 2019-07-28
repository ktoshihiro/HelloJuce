/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


template<class ButtonType>
auto makeButton(ButtonType *buttonToMakeUnique) -> std::unique_ptr<ButtonType> {
    return std::unique_ptr<ButtonType>(buttonToMakeUnique);
}


//==============================================================================
MainComponent::MainComponent() {
//    heapButton.reset(
//            new HeapButtonWrapper<TextButton>([]() {
//                DBG("you clicked the heap");
//            }, makeButton(new TextButton("heap button"))));
    heapButton.reset(
            new HeapButtonWrapper<TextButton>([]() {
                DBG("you clicked the heap");
            }, new TextButton("heap button")));

    tb.onClick = []() {
        std::cout << "TextButton tb" << std::endl;
    };

    addAndMakeVisible(static_cast<Component *>(button));
    addAndMakeVisible((Component *) *heapButton);
    addAndMakeVisible(tb);

    setSize(600, 400);
}

MainComponent::~MainComponent() {
}

//==============================================================================
void MainComponent::paint(Graphics &g) {
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

    g.setFont(Font(16.0f));
    g.setColour(Colours::red);
    g.drawText("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainComponent::resized() {
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

//    button->setBounds(JUCE_LIVE_CONSTANT(10),
//                      JUCE_LIVE_CONSTANT(10), 100, 30);
//    (*heapButton)->setBounds(JUCE_LIVE_CONSTANT(210),
//                             JUCE_LIVE_CONSTANT(10), 100, 30);
    button->setBounds(10, 10, 100, 30);
    (*heapButton)->setBounds(210, 10, 100, 30);
    tb.setBounds(10, 60, 100, 30);
}
