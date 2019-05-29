#pragma once

#include "input.hpp"
#include <SFML/System/Clock.hpp>
#include <cstring>
#include <set>
#include <memory>

namespace gamelib2 {

enum ControllerEventID {
    NoEvent = 0,
    Fire,
    FireTap,
    DPadLeft,
    DPadRight,
    DPadUp,
    DPadDown
};

enum ControllerEventStatus { Released = 0, Pressed };

struct ControllerEvent {
    ControllerEvent() {
        id = NoEvent;
        status = Released;
        param = 0;
    }

    ControllerEvent(ControllerEventID i, ControllerEventStatus s, int p = 0) {
        id = i;
        status = s;
        param = p;
    }

    ControllerEventID id;
    ControllerEventStatus status;
    int param;
};

class ControllerListener {
public:
    virtual ~ControllerListener() = default;
    virtual void onControllerEvent(ControllerEvent event) = 0;
};

class Controller {

public:
    Controller(InputDevice &i);
    virtual ~Controller() = default;
    virtual void update();

    void setListener(ControllerListener *l);
    int fire_ticks = 0;
    InputDevice &input;

protected:
    ControllerListener *listener = nullptr;
    bool wait_for_release = false;
    void notify(ControllerEvent event);

    static const int fire_tap_length = 15;
};
} // namespace gamelib2