#include "device.hpp"
#include <iostream>
namespace gamelib2 {

Controller::Controller(gamelib2::InputDevice &i)
  : input(i) {
}

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
            notify(ControllerEvent(Fire, Released,
                                   input.states[InputState::FireLengthCached]));
        }

    } else {
        if (input.states[InputState::FireDown]) {
            notify(ControllerEvent(Fire, Pressed));
        }
    }

    //
    // Left
    //
    if (!old_states[InputState::Left]) {
        if (input.states[InputState::Left]) {
            notify(ControllerEvent(DPadLeft, Pressed));
        }
    } else {
        if (!input.states[InputState::Left]) {
            notify(ControllerEvent(DPadLeft, Released));
        }
    }

    //
    // Right
    //
    if (!old_states[InputState::Right]) {
        if (input.states[InputState::Right]) {
            notify(ControllerEvent(DPadRight, Pressed));
        }
    } else {
        if (!input.states[InputState::Right]) {
            notify(ControllerEvent(DPadRight, Released));
        }
    }

    //
    // Up
    //
    if (!old_states[InputState::Up]) {
        if (input.states[InputState::Up]) {
            notify(ControllerEvent(DPadUp, Pressed));
        }
    } else {
        if (!input.states[InputState::Up]) {
            notify(ControllerEvent(DPadUp, Released));
        }
    }

    //
    // Down
    //
    if (!old_states[InputState::Down]) {
        if (input.states[InputState::Down]) {
            notify(ControllerEvent(DPadDown, Pressed));
        }
    } else {
        if (!input.states[InputState::Down]) {
            notify(ControllerEvent(DPadDown, Released));
        }
    }
}

// ------------------------------------------------------------------------------------------------------------
// setListener
// ------------------------------------------------------------------------------------------------------------
void Controller::setListener(ControllerListener *l) {
    listener = l;
}

// ------------------------------------------------------------------------------------------------------------
// Notify
// ------------------------------------------------------------------------------------------------------------
void Controller::notify(ControllerEvent event) {
    listener->onControllerEvent(event);
}

} // namespace gamelib2
