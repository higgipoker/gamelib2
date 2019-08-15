#pragma once
#include "../widgets/widget.hpp"
#include "../widgets/sprite.hpp"
#include "../input/input.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <string>
#include <vector>

namespace gamelib2{

  enum Layer{
    BG=0,
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

  class Joystick : public Widget{
  public:
    Joystick() = default;
    ~Joystick();
    void init( std::vector<std::string> &in_filenames);
    virtual void render(sf::RenderTarget &target) override;
    void update(const int in_states[]);

  private:
    int x = 0;
    int y = 0;
    bool inited = false;
    std::vector<Sprite*> sprites;
    int states[InputState::Totalevents]{};
  };

}
