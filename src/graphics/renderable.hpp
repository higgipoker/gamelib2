#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace gamelib2 {
class Renderable : public sf::Sprite {
 public:
  Renderable();
  virtual void render(sf::RenderTarget& target) = 0;
  bool visible = true;
  int z_order = 0;
};
}  // namespace gamelib2
