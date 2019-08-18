#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include "../math/vector.hpp"
#include "../types.hpp"

namespace gamelib2 {

class Collision {
 public:
  /**
   * @brief circle and circle
   * @param c1
   * @param c2
   * @return
   */
  static bool collides(const sf::CircleShape &c1, const sf::CircleShape &c2);

  /**
   * @brief point and circle
   * @param point
   * @param circle
   * @return
   */
  static bool collides(const Vector3 &point, const sf::CircleShape &circle);

  /**
   * @brief point and triangle
   * @param point
   * @param triangle
   * @return
   */
  static bool collides(const Vector3 &point, const Triangle &triangle);
};

}  // namespace gamelib2
