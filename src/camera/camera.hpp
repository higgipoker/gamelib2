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
  /**
   * @brief init
   * @param width
   * @param height
   */
  void init(int width, int height);

  /**
   * @brief update
   * @param dt
   */
  void step(float dt) override;

  /**
   * @brief setWorldRect
   * @param world_rect
   */
  void setWorldRect(const sf::Rect<int> &world_rect);

  /**
   * @brief follow
   * @param e
   */
  void follow(Entity *e);

  /**
   * @brief letterbox
   */
  void letterbox();

  /**
   * @brief onWindowResized
   * @param x
   * @param y
   */
  void onWindowResized(int x, int y);

  /**
   * @brief getViewInWorld
   * @return
   */
  sf::FloatRect getViewInWorld();

  ///
  sf::View view;

 protected:
  // following something?
  Entity *target = nullptr;

  // whole game world
  sf::Rect<int> world;

  // helper
  void update_position();
};

}  // namespace gamelib2
