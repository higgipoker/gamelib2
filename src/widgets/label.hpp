#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include "widget.hpp"

namespace gamelib2 {

/**
 * @brief The Sprite class
 */
class Label : public Widget {
 public:
  /**
   * @brief Label
   * @param fontname
   */
  Label(const std::string &fontname);

  /**
   * @brief render
   * @param target
   */
  void render(sf::RenderTarget &target) override;

  /**
   * @brief setPosition
   * @param x
   * @param y
   */
  void setPosition(float x, float y) override;

  /**
   * @brief setText
   * @param l
   */
  void setText(std::string l);

  /**
   * @brief setText
   * @param a_number
   */
  void setText(int a_number);

  /**
   * @brief setColor
   * @param c
   */
  void setColor(sf::Color c);

  /**
   * @brief setSize
   * @param s
   */
  void setSize(int s);

  /**
   * @brief setCenter
   * @param x
   * @param y
   */
  void setCenter(int x, int y);

  /**
   * @brief bounds
   * @return
   */
  sf::FloatRect bounds();

 protected:
  sf::Font font;
  sf::Text text;
  std::string label;
};

}  // namespace gamelib2
