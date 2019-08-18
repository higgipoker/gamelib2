#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "../graphics/autotexture.hpp"
#include "../widgets/widget.hpp"

namespace gamelib2 {

/**
 * @brief The Sprite class
 */
class Sprite : public Widget {
 public:
  /**
   * @brief Sprite
   */
  Sprite(const std::string &_name);

  /**
   * @brief Sprite
   * @param a_filename
   * @param a_rows
   * @param a_cols
   */
  Sprite(const std::string &_name, const std::string &a_filename, int a_rows,
         int a_cols);
  ~Sprite() override;

  /**
   * @brief render
   * @param target
   */
  void render(sf::RenderTarget &target) override;

  /**
   * @brief init
   * @param a_filename
   * @param a_rows
   * @param a_cols
   */
  void init(std::string a_filename, int a_rows, int a_cols);

  /**
   * @brief move
   * @param dx
   * @param dy
   */
  void move(float dx, float dy) override;

  /**
   * @brief setPosition
   * @param x
   * @param y
   */
  void setPosition(float x, float y) override;

  /**
   * @brief scale
   * @param x
   * @param y
   */
  void scale(float x, float y) override;

  /**
   * @brief scale
   * @return
   */
  sf::Vector2f scale() override;

  /**
   * @brief connectShadow
   * @param spr
   */
  void connectShadow(Sprite *spr);

  /**
   * @brief setFrame
   * @param a_frame
   */
  void setFrame(int a_frame);

  /**
   * @brief getFrame
   * @return
   */
  int getFrame();

  /**
   * @brief bounds
   * @return
   */
  sf::FloatRect bounds() override;

  /**
   * @brief position
   * @return
   */
  sf::Vector2f position() override;

  /**
   * @brief swapColors
   * @param palette
   */
  void swapColors(const std::vector<std::pair<sf::Color, sf::Color>> &palette);

  /**
   * @brief setOrigin
   * @param in_x
   * @param in_y
   */
  void setOrigin(float in_x, float in_y);

  float image_width = 0;
  float image_height = 0;
  bool has_shadow = false;

  /**
   * @brief getShadow
   * @return
   */
  Sprite *getShadow();
  Sprite *shadow = nullptr;

 private:
  AutoTexture texture;
  sf::Texture unique_texture;
  std::vector<sf::IntRect> rects;
  sf::Sprite sprite;
  int current_frame = 0;
};

}  // namespace gamelib2
