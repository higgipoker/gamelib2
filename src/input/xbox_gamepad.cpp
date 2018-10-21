/****************************************************************************
 * CopyRight (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
#include "xbox_gamepad.hpp"
#include <map>
namespace gamelib2 {

/// map button id's to string identifiers
static std::map<int, std::string> buttons{
  {0, "A"},     {1, "B"},       {2, "X"},        {3, "Y"},     {4, "LB"},
  {5, "RB"},    {6, "LTRIGER"}, {7, "RTRIGGER"}, {8, "BACK"},  {9, "START"},
  {10, "XBOX"}, {11, "LCKICK"}, {12, "RCLICK"},  {13, "Left"}, {14, "Right"},
  {15, "Up"},   {16, "Down"},
};

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void XboxController::update() {

    sf_joystick_index = 1;

    // fire button
    states[InputState::FireUp] = 0;
    if (A() || B() || X() || Y()) {
        if (states[InputState::FireDown] == 0) {
            states[InputState::FireDown] = 1;
            fire_ticks = 0;
        } else {
            states[InputState::FireLength] = fire_ticks++;
        }
    }

    else if (states[InputState::FireDown] == 1) {
        states[InputState::FireUp] = 1;
        states[InputState::FireDown] = 0;
        states[InputState::FireLengthCached] = fire_ticks;
        states[InputState::FireLength] = 0;
    }

    // directions
    states[InputState::Up] = states[InputState::Down] =
      states[InputState::Left] = states[InputState::Right] = 0;

    if (Up()) {
        states[InputState::Up] = 1;
    }

    if (Down()) {
        states[InputState::Down] = 1;
    }

    if (Left()) {
        states[InputState::Left] = 1;
    }

    if (Right()) {
        states[InputState::Right] = 1;
    }
}

// -----------------------------------------------------------------------------
// isConnected
// -----------------------------------------------------------------------------
bool XboxController::isConnected() {
    if (sf_joystick_index <= sf::Joystick::Count)
        return sf::Joystick::isConnected(sf_joystick_index);

    return false;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool XboxController::A() {
    return sf::Joystick::isButtonPressed(sf_joystick_index, 0);
}

bool XboxController::B() {
    return sf::Joystick::isButtonPressed(sf_joystick_index, 1);
}

bool XboxController::X() {
    return sf::Joystick::isButtonPressed(sf_joystick_index, 2);
}

bool XboxController::Y() {
    return sf::Joystick::isButtonPressed(sf_joystick_index, 3);
}

bool XboxController::LeftBumper() {
    return sf::Joystick::isButtonPressed(sf_joystick_index, 4);
}

bool XboxController::RightBumper() {
    return sf::Joystick::isButtonPressed(sf_joystick_index, 5);
}

bool XboxController::LeftTriggerPressed() {
    return sf::Joystick::isButtonPressed(sf_joystick_index, 6);
}

bool XboxController::RightTriggerPressed() {
    return sf::Joystick::isButtonPressed(sf_joystick_index, 7);
}

bool XboxController::Back() {
    return sf::Joystick::isButtonPressed(sf_joystick_index, 8);
}

bool XboxController::Start() {
    return sf::Joystick::isButtonPressed(sf_joystick_index, 9);
}

bool XboxController::XboxButton() {
    return sf::Joystick::isButtonPressed(sf_joystick_index, 10);
}

bool XboxController::LeftThumbstickClick() {
    return sf::Joystick::isButtonPressed(sf_joystick_index, 11);
}

bool XboxController::RightThumbstickClick() {
    return sf::Joystick::isButtonPressed(sf_joystick_index, 12);
}

bool XboxController::DpadLeft() {
    return sf::Joystick::isButtonPressed(sf_joystick_index, 13);
}

bool XboxController::DpadRight() {
    return sf::Joystick::isButtonPressed(sf_joystick_index, 14);
}

bool XboxController::DpadUp() {
    return sf::Joystick::isButtonPressed(sf_joystick_index, 15);
}

bool XboxController::DpadDown() {
    return sf::Joystick::isButtonPressed(sf_joystick_index, 16);
}

float XboxController::LeftTriggerValue() {
    return sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::Z);
}

float XboxController::RightTriggerValue() {
    return sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::R);
}

bool XboxController::LeftTrigger() {
    return LeftTriggerValue() > trigger_threshold;
}

bool XboxController::RightTrigger() {
    return RightTriggerValue() > trigger_threshold;
}

sf::Vector2f XboxController::LeftThumbstick() {
    return {sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::X),
            sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::Y)};
}

sf::Vector2f XboxController::RightThumbstick() {
    return {sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::U),
            sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::V)};
}

bool XboxController::Up() {
    return DpadUp() || LeftThumbstick().y < -thumbstick_threshold;
}

bool XboxController::Down() {
    return DpadDown() || LeftThumbstick().y > thumbstick_threshold;
}

bool XboxController::Left() {
    return DpadLeft() || LeftThumbstick().x < -thumbstick_threshold;
}

bool XboxController::Right() {
    return DpadRight() || LeftThumbstick().x > thumbstick_threshold;
}
} // namespace gamelib2
