#pragma once

#include "input.hpp"
#include <SFML/Window.hpp>
#include <iostream>

namespace gamelib2 {

class XboxController : public InputDevice {

public:
    void update() override;
    bool isConnected();

    bool A();
    bool B();
    bool X();
    bool Y();

    bool RightBumper();
    bool LeftBumper();

    bool LeftThumbstickClick();
    bool RightThumbstickClick();

    bool Start();
    bool Back();
    bool XboxButton();

    bool DpadUp();
    bool DpadDown();
    bool DpadLeft();
    bool DpadRight();

    bool LeftTriggerPressed();
    bool RightTriggerPressed();

    float LeftTriggerValue();
    float RightTriggerValue();

    bool LeftTrigger();
    bool RightTrigger();

    sf::Vector2f LeftThumbstick();
    sf::Vector2f RightThumbstick();

    bool Up();
    bool Down();
    bool Left();
    bool Right();

private:
    int sf_joystick_index = 0;
    float trigger_threshold = 0;
    float thumbstick_threshold = 50.0f;
};

} // namespace gamelib2
