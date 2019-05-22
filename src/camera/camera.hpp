#pragma once

#include <SFML/Graphics/View.hpp>
#include "../game/entity.hpp"

namespace gamelib2 {

/**
 * @brief The Camera class
 */
class Camera : public Entity {
 public:
  virtual ~Camera() override = default;
  void init(int width, int height);
  void update(float dt) override;
  void setWorldRect(const sf::Rect<int> &world_rect);
  void follow(Entity *e);
  void letterbox();
  void onWindowResized(int x, int y);
  sf::FloatRect getViewInWorld();
  sf::View view;

 protected:
  // following something?
  Entity *target = nullptr;

  /// whole game world
  sf::Rect<int> world;

  // helper
  void update_position();
};

}  // namespace gamelib2
