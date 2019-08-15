#pragma once
#include "input.hpp"

namespace gamelib2 {
class Keyboard : public InputDevice {
public:
    void update() override;
};

} // namespace gamelib2
