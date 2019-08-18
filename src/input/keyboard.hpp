#pragma once
#include "input.hpp"

namespace gamelib2 {
/**
 * @brief The Keyboard class
 */
class Keyboard : public InputDevice {
 public:
  /**
   * @brief update
   */
  void update() override;
};

}  // namespace gamelib2
