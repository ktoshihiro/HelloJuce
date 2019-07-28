/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


template<typename ButtonType>
class ButtonWrapper : public Button::Listener {
public:
    template<typename ... Args>
    // optional parameter typename
    ButtonWrapper(std::function<void()> onClickHandler, Args &&... args)
            :onClick(std::move(onClickHandler)),
             button(std::forward<Args>(args) ...) {
        button.addListener(this);
    }

    ~ButtonWrapper() {
        button.removeListener(this);
    }

    void buttonClicked(Button *b) override {
        if (onClick)
            onClick();
    }

    explicit operator Component *() {
        return &button;
    }

    explicit operator Component &() {
        return button;
    }

    Button *operator->() {
        return &button;
    }

private:
    std::function<void()> onClick;
    ButtonType button;
};


template<class ButtonType>
class HeapButtonWrapper : public Button::Listener {
public:
//    template<typename ... Args>
//    // optional parameter typename
//    HeapButtonWrapper(std::function<void()> onClickHandler, Args &&... args)
//            :onClick(std::move(onClickHandler)),
//             button(std::forward<Args>(args) ...) {
//        button.addListener(this);
//    }
    HeapButtonWrapper(std::function<void()> onClickHandler, std::unique_ptr<ButtonType> heapButton)
            : onClick(std::move(onClickHandler)), button(std::move(heapButton)) {
        setupButton();
    }

//    HeapButtonWrapper(std::function<void()> onClickHandler, ButtonType *rawButtonPtr)
//            : onClick(std::move(onClickHandler)), button(rawButtonPtr) {
//        setupButton();
//    }
    HeapButtonWrapper(std::function<void()> onClickHandler, ButtonType *rawButtonPtr)
            : HeapButtonWrapper(onClickHandler, std::unique_ptr<ButtonType>(rawButtonPtr)) {}

    void setupButton() {
        jassert(button.get() != nullptr);
        if (button.get())
            button->addListener(this);
    }

    ~HeapButtonWrapper() {
        if (button.get())
            button->removeListener(this);
    }

    void buttonClicked(Button *b) override {
        if (onClick)
            onClick();
    }

    // because out unique_ptr<> might not be holding anything
    explicit operator Component *() const {
        return button.get();
    }

    ButtonType *operator->() {
        return button.get();
    }

private:
    std::function<void()> onClick;
    std::unique_ptr<ButtonType> button; // ここが変わった
};


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public Component {
public:
    //==============================================================================
    MainComponent();

    ~MainComponent();

    //==============================================================================
    void paint(Graphics &) override;

    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    ButtonWrapper<TextButton> button{[]() {
        DBG("Text Button Clicked");
    }, "text button"};
    std::unique_ptr<HeapButtonWrapper<TextButton>> heapButton;
    TextButton tb{"TextButton"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
