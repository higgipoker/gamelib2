#pragma once
#include "../viewer/viewer.hpp"
#include "keyboardlistener.hpp"
#include <SFML/Window.hpp>
#include <map>
#include <memory>

namespace gamelib2 {
class Keyboard {
  public:
    std::map<input_event, int> event_states;
};

} // namespace gamelib2
