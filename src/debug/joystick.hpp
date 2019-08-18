#pragma once
#include "../input/input.hpp"
#include "../widgets/sprite.hpp"
#include "../widgets/widget.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <string>
#include <vector>

namespace gamelib2 {

/**
 * @brief The Layer enum
 */
enum Layer {
  BG = 0,
  DPAD_LEFT,
  DPAD_RIGHT,
  DPAD_UP,
  DPAD_DOWN,
  DPAD_CENTERED,
  BUTTON_GREEN,
  BUTTON_RED,
  BUTTON_YELLOW,
  BUTTON_BLUE,
  ANALOG_LEFT,
  ANALOG_RIGHT
};

/**
 * @brief The Joystick class
 */
class Joystick : public Widget {
 public:
  Joystick(const std::string &_name) : Widget(_name) {}
  ~Joystick();

  /**
   * @brief init
   * @param in_filenames
   */
  void init(std::vector<std::string> &in_filenames);

  /**
   * @brief update
   * @param in_states
   */
  void update(const int in_states[]);

  /**
   * @brief render
   * @param target
   */
  virtual void render(sf::RenderTarget &target) override;

 private:
  int x = 0;
  int y = 0;
  bool inited = false;
  std::vector<Sprite *> sprites;
  int states[InputState::Totalevents]{};
};

}  // namespace gamelib2
