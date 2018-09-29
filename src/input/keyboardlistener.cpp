#include "keyboardlistener.hpp"
namespace gamelib2 {

void KeyboardListener::onEvent(const sf::Event& in_event) {
  event = in_event;
  new_event = true;
}
bool KeyboardListener::popEvent() {
  if (new_event) {
    new_event = false;
    return true;
  } else {
    return false;
  }
}
}  // namespace gamelib2
