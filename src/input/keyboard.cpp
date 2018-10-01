#include "keyboard.hpp"
#include <SFML/Window/Keyboard.hpp>

#include <iostream>

namespace gamelib2 {

// -----------------------------------------------------------------------------
// ControllerState::Update
// -----------------------------------------------------------------------------
void Keyboard::update() {

    states[ControllerState::FireUp] = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        states[ControllerState::Up] = 1;
    } else {
        states[ControllerState::Up] = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        states[ControllerState::Down] = 1;
    } else {
        states[ControllerState::Down] = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        states[ControllerState::Left] = 1;
    } else {
        states[ControllerState::Left] = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        states[ControllerState::Right] = 1;
    } else {
        states[ControllerState::Right] = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        if (states[ControllerState::FireDown] == 0) {
            states[ControllerState::FireDown] = 1;
            fire_ticks = 0;
        } else {
            states[ControllerState::FireLength] = fire_ticks++;
            std::cout << "fire down" << std::endl;
        }
    } else if (states[ControllerState::FireDown] == 1) {
        states[ControllerState::FireUp] = 1;
        states[ControllerState::FireDown] = 0;
        states[ControllerState::FireLengthCached] = fire_ticks;
        states[ControllerState::FireLength] = 0;
        std::cout << "fire up (" << fire_ticks << ")" << std::endl;
    }
}

} // namespace gamelib2
