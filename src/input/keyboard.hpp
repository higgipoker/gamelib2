#pragma once
#include "input.hpp"

namespace gamelib2 {
class Keyboard : public Input {
public:
    void update() override;
};

} // namespace gamelib2
