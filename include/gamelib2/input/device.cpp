#include "device.hpp"
#include <iostream>
namespace gamelib2 {

Controller::Controller(gamelib2::InputDevice &i) : input(i) {}

void Controller::update() {
  // for comparison for events (chaged statuses)
  int old_states[InputState::Totalevents] = {
      input.states[0], input.states[1], input.states[2], input.states[3],
      input.states[4], input.states[5], input.states[6], input.states[7],
      input.states[8], input.states[9], input.states[10]};

  input.update();

  //
  // Fire
  //
  if (old_states[InputState::FireDown]) {
    if (input.states[InputState::FireUp]) {
      if (input.states[InputState::FireLengthCached] < fire_tap_length) {
        notify(ControllerEvent(FireTap, Released));
      } else {
        notify(ControllerEvent(Fire, Released,
                               input.states[InputState::FireLengthCached]));
      }
    }

  } else {
    if (input.states[InputState::FireDown]) {
      notify(ControllerEvent(Fire, Pressed));
    }
  }
}

// -----------------------------------------------------------------------------
// setListener
// -----------------------------------------------------------------------------
void Controller::setListener(ControllerListener *l) { listener = l; }

// -----------------------------------------------------------------------------
// Notify
// -----------------------------------------------------------------------------
void Controller::notify(ControllerEvent event) {
  if (listener) {
    listener->onControllerEvent(event);
  }
}

} // namespace gamelib2
