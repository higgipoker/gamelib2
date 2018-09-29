#ifndef KEYBOARDLISTENER_HPP
#define KEYBOARDLISTENER_HPP
#include <SFML/Window.hpp>
#include <iostream>

namespace gamelib2 {
class KeyboardListener {
 public:
  KeyboardListener() {
  }
  ~KeyboardListener() {
  }

  void onEvent(const sf::Event &in_event);
  bool popEvent();
  sf::Event event;

 private:
  bool new_event = false;
};
}  // namespace gamelib2

#endif  // KEYBOARDLISTENER_HPP
