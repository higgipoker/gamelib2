#pragma once

#include <string>

namespace gamelib2 {

// base class for states
class State {
public:
    // construct / destruct
    State();
    virtual ~State();

    // state started
    virtual void start() = 0;

    // main update
    virtual void update(const float _dt) = 0;

    // state over
    virtual void end() = 0;

    // check for end state
    virtual bool finished() = 0;

    // change to next state
    virtual void changeToNextState() = 0;

    // identifier
    std::string name;
};
} // namespace gamelib2
