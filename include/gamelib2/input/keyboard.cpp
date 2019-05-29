#include "keyboard.hpp"
#include <SFML/Window/Keyboard.hpp>

#include <iostream>

namespace gamelib2 {

// -----------------------------------------------------------------------------
// ControllerState::Update
// -----------------------------------------------------------------------------
void Keyboard::update() {

  states[InputState::FireUp] = 0;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    states[InputState::Up] = 1;
  } else {
    states[InputState::Up] = 0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    states[InputState::Down] = 1;
  } else {
    states[InputState::Down] = 0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    states[InputState::Left] = 1;
  } else {
    states[InputState::Left] = 0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    states[InputState::Right] = 1;
  } else {
    states[InputState::Right] = 0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
    if (states[InputState::FireDown] == 0) {
      states[InputState::FireDown] = 1;
      fire_ticks = 0;
    } else {
      states[InputState::FireLength] = fire_ticks++;
    }
  } else if (states[InputState::FireDown] == 1) {
    states[InputState::FireUp] = 1;
    states[InputState::FireDown] = 0;
    states[InputState::FireLengthCached] = fire_ticks;
    states[InputState::FireLength] = 0;
  }
}

} // namespace gamelib2
