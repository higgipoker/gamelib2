#pragma once
#include <SFML/System/Clock.hpp>
#include <cstring>

namespace gamelib2 {

enum ControllerState {
    Up = 0,
    Down,
    Left,
    Right,
    FireDown,
    FireUp,
    FireLength,
    FireLengthCached,
    SingleTap,
    DoubleTap,
    FirePress,
    Totalevents
};

class Controller {

public:
    Controller() = default;
    virtual ~Controller() = default;
    virtual void update() = 0;
    void reset() { memset(states, 0, sizeof(states)); }
    int states[static_cast<int>(ControllerState::Totalevents)]{};
    int fire_ticks;

protected:
};
} // namespace gamelib2
