#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "../graphics/autotexture.hpp"
#include "../widgets/widget.hpp"
#include "spriteanimation.hpp"

namespace gamelib2 {

/**
 * @brief The Sprite class
 */
class Sprite : public Widget {
 public:
  Sprite();
  Sprite(const std::string &a_filename, int a_rows, int a_cols);
  ~Sprite() override;

  void update() override;
  void render(sf::RenderTarget &target) override;
  void init(std::string a_filename, int a_rows, int a_cols);
  void animate() override;
  void move(float dx, float dy) override;
  void setPosition(float x, float y) override;
  void scale(float x, float y) override;
  sf::Vector2f scale() override;
  void connectShadow(Sprite *spr);
  void setFrame(int a_frame);
  int getFrame();
  void addAnimation(const SpriteAnimation &a_sprite_anim) override;
  void addAnimation(const std::string &animname, int frametime, bool loopanim,
                    const std::vector<int> &framelist) override;
  sf::FloatRect bounds() override;
  sf::Vector2f position() override;
  void swapColors(const std::vector<std::pair<sf::Color, sf::Color>> &palette);

  float image_width = 0;
  float image_height = 0;
  bool has_shadow = false;

  Sprite *getShadow();
  Sprite *shadow = nullptr;

 private:
  AutoTexture texture;
  sf::Texture unique_texture;
  std::vector<sf::IntRect> rects;
  sf::Sprite sprite;
};

}  // namespace gamelib2
