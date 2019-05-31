#include "keyboard.hpp"
#include <SFML/Window/Keyboard.hpp>

#include <iostream>

namespace gamelib2 {

// -----------------------------------------------------------------------------
// ControllerState::Update
// -----------------------------------------------------------------------------
void Keyboard::update() {

  states[InputState::FireUp] = 0;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    states[InputState::Up] = 1;
  } else {
    states[InputState::Up] = 0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    states[InputState::Down] = 1;
  } else {
    states[InputState::Down] = 0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    states[InputState::Left] = 1;
  } else {
    states[InputState::Left] = 0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    states[InputState::Right] = 1;
  } else {
    states[InputState::Right] = 0;
  }

  // fire 1
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
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

  // fire 2
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
    if (states[InputState::FireDown2] == 0) {
      states[InputState::FireDown2] = 1;
      fire_ticks = 0;
    } else {
      states[InputState::FireLength2] = fire_ticks++;
    }
  } else if (states[InputState::FireDown2] == 1) {
    states[InputState::FireUp2] = 1;
    states[InputState::FireDown2] = 0;
    states[InputState::FireLengthCached2] = fire_ticks;
    states[InputState::FireLength2] = 0;
  }

  // fire 3
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
    if (states[InputState::FireDown3] == 0) {
      states[InputState::FireDown3] = 1;
      fire_ticks = 0;
    } else {
      states[InputState::FireLength3] = fire_ticks++;
    }
  } else if (states[InputState::FireDown3] == 1) {
    states[InputState::FireUp3] = 1;
    states[InputState::FireDown3] = 0;
    states[InputState::FireLengthCached3] = fire_ticks;
    states[InputState::FireLength3] = 0;
  }

  // fire 4
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
    if (states[InputState::FireDown4] == 0) {
      states[InputState::FireDown4] = 1;
      fire_ticks = 0;
    } else {
      states[InputState::FireLength4] = fire_ticks++;
    }
  } else if (states[InputState::FireDown4] == 1) {
    states[InputState::FireUp4] = 1;
    states[InputState::FireDown4] = 0;
    states[InputState::FireLengthCached4] = fire_ticks;
    states[InputState::FireLength4] = 0;
  }
}

} // namespace gamelib2
