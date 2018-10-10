#pragma once
#include "widget.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

namespace gamelib2 {

/**
 * @brief The Sprite class
 */
class Label : public Widget {
public:
  Label(const std::string &fontname);
  void render(sf::RenderTarget &target) override;
  void setPosition(float x, float y) override;
  void setText(std::string l);
  void setColor(sf::Color c);
  void setSize(unsigned int s);
  void setCenter(unsigned int x, unsigned int y);
  sf::FloatRect bounds();

protected:
  sf::Font font;
  sf::Text text;
  std::string label;
};

} // namespace gamelib2
