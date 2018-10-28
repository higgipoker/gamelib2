#pragma once

#include "../graphics/autotexture.hpp"
#include "../widgets/widget.hpp"
#include "spriteanimation.hpp"
#include <SFML/Graphics/Sprite.hpp>

namespace gamelib2 {

/**
 * @brief The Sprite class
 */
class Sprite : public Widget {
public:
  Sprite();
  Sprite(const std::string &a_filename, int a_rows, int a_cols);
  ~Sprite() override;

  void render(sf::RenderTarget &target) override;
  void init(std::string a_filename, int a_rows, int a_cols);
  void animate() override;
  void move(float dx, float dy) override;
  void setPosition(float x, float y) override;
  void scale(float x, float y) override;
  sf::Vector2f scale() override;
  void connectShadow(std::unique_ptr<Sprite> spr);
  void setFrame(unsigned int a_frame);
  unsigned int getFrame();
  void addAnimation(const SpriteAnimation &a_sprite_anim) override;
  void addAnimation(const std::string &animname, unsigned int frametime,
                    bool loopanim,
                    const std::vector<unsigned int> &framelist) override;
  sf::FloatRect bounds() override;
  sf::Vector2f position() override;
  void swapColors(const std::vector<std::pair<sf::Color, sf::Color>> &palette);

  float image_width = 0;
  float image_height = 0;
  bool has_shadow = false;

  Sprite *getShadow();

  std::unique_ptr<Sprite> shadow;

private:
  AutoTexture texture;
  sf::Texture unique_texture;
  std::vector<sf::IntRect> rects;
  sf::Sprite sprite;
};

} // namespace gamelib2
