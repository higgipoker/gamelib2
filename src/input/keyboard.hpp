#pragma once
#include "controller.hpp"

namespace gamelib2 {
class Keyboard : public Controller {
public:
    void update() override;
};

} // namespace gamelib2
