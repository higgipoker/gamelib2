#include "sprite.hpp"

#include <cassert>
#include <iostream>

#include "../math/vector.hpp"

namespace gamelib2 {

// -----------------------------------------------------------------------------
// Sprite
// -----------------------------------------------------------------------------
Sprite::Sprite() = default;

// -----------------------------------------------------------------------------
// Sprite
// -----------------------------------------------------------------------------
Sprite::Sprite(const std::string &a_filename, int a_rows, int a_cols) {
  init(a_filename, a_rows, a_cols);
}

// -----------------------------------------------------------------------------
// ~Sprite
// -----------------------------------------------------------------------------
Sprite::~Sprite() = default;

// -----------------------------------------------------------------------------
// init
// -----------------------------------------------------------------------------
void Sprite::init(std::string a_filename, int a_rows, int a_cols) {
  texture.Initialize(std::move(a_filename));
  sprite.setTexture(texture());
  image_width = texture().getSize().x / static_cast<float>(a_cols);
  image_height = texture().getSize().y / static_cast<float>(a_rows);

  // set up the coordinates of each frame
  int sprite_width = static_cast<int>(texture().getSize().x) / a_cols;
  int sprite_height = static_cast<int>(texture().getSize().y) / a_rows;

  sprite.setOrigin(sprite_width / 2, sprite_height / 2);

  for (int row = 0; row < a_rows; row++) {
    for (int col = 0; col < a_cols; col++) {
      sf::IntRect rect(col * sprite_width, row * sprite_height, sprite_width,
                       sprite_height);
      rects.push_back(rect);
    }
  }
  sprite.setTextureRect(rects[0]);
}

// -----------------------------------------------------------------------------
// render
// -----------------------------------------------------------------------------
void Sprite::render(sf::RenderTarget &target) {
  target.draw(sprite);
  Widget::render(target);
}

// -----------------------------------------------------------------------------
// setFrame
// -----------------------------------------------------------------------------
void Sprite::setFrame(unsigned int a_frame) {
  // no bounds check, crash on out-of-range, should never happen
  sprite.setTextureRect(rects[a_frame]);
}

// -----------------------------------------------------------------------------
// setFrame
// -----------------------------------------------------------------------------
unsigned int Sprite::getFrame() {
  if (current_animation)
    return current_animation->currentFrame();

  return 0;
}

// -----------------------------------------------------------------------------
// addAnimation
// -----------------------------------------------------------------------------
void Sprite::addAnimation(const SpriteAnimation &a_sprite_anim) {
  animations.insert(
      std::make_pair(a_sprite_anim.name, std::move(a_sprite_anim)));
}

// ----------------------------------------------------------------------------------
// AddAnimation
// ----------------------------------------------------------------------------------
void Sprite::addAnimation(const std::string &animname, unsigned int frametime,
                          bool loopanim,
                          const std::vector<unsigned int> &framelist) {
  SpriteAnimation anim(animname, frametime, loopanim, std::move(framelist));
  addAnimation(anim);
}

// -----------------------------------------------------------------------------
// animate
// -----------------------------------------------------------------------------
void Sprite::animate() {
  if (current_animation) {
    setFrame(current_animation->update());
  }
}

// -----------------------------------------------------------------------------
// getBounds
// -----------------------------------------------------------------------------
sf::FloatRect Sprite::bounds() { return sprite.getGlobalBounds(); }

// -----------------------------------------------------------------------------
// move
// -----------------------------------------------------------------------------
void Sprite::move(float dx, float dy) {
  sprite.move(dx, dy);
  Widget::move(dx, dy);
}

// -----------------------------------------------------------------------------
// position
// -----------------------------------------------------------------------------
sf::Vector2f Sprite::position() { return sprite.getPosition(); }

// -----------------------------------------------------------------------------
// scale
// -----------------------------------------------------------------------------
void Sprite::scale(float x, float y) {
  sprite.setScale(x, y);
  if (shadow) {
    shadow->scale(x, y);
  }
}

// -----------------------------------------------------------------------------
// setPosition
// -----------------------------------------------------------------------------
void Sprite::setPosition(float x, float y) {
  float dx = this->position().x - x;
  float dy = this->position().y - y;
  sprite.setPosition(x, y);
  if(shadow){
      shadow->setPosition(x,y);
  }

  Widget::move(dx, dy);
}

// -----------------------------------------------------------------------------
// getScale
// -----------------------------------------------------------------------------
sf::Vector2f Sprite::scale() { return sprite.getScale(); }

// -----------------------------------------------------------------------------
// getScale
// -----------------------------------------------------------------------------
void Sprite::connectShadow(std::unique_ptr<gamelib2::Sprite> spr) {
  has_shadow = true;
  shadow = std::move(spr);
}

// -----------------------------------------------------------------------------
// getShadow
// -----------------------------------------------------------------------------
std::shared_ptr<Sprite> Sprite::getShadow() { return shadow; }

// -----------------------------------------------------------------------------
// swapColors
// -----------------------------------------------------------------------------
void Sprite::swapColors(
    const std::vector<std::pair<sf::Color, sf::Color>> &palette) {

  // get a copy of the original texture
  sf::Image img = texture().copyToImage();

  // replace the colors in the copy
  for (auto &colours : palette) {
    for (auto x = 0; x < img.getSize().x; ++x) {
      for (auto y = 0; y < img.getSize().y; ++y) {
        if (img.getPixel(x, y) == colours.first) {
          img.setPixel(x, y, colours.second);
        }
      }
    }
  }

  // load the copy into the unique texture
  unique_texture.loadFromImage(img);

  // use the unique texture for the sprite
  sprite.setTexture(unique_texture);
}
} // namespace gamelib2
