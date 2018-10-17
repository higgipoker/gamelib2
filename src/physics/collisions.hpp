#pragma once
#include "../types.hpp"
#include "../math/vector.hpp"
#include <SFML/Graphics/CircleShape.hpp>

namespace gamelib2 {

class Collision {
public:
    // circle and circle
    static bool collides(const sf::CircleShape &c1, const sf::CircleShape &c2);

    // point and circle
    static bool collides(const Vector3 &point, const sf::CircleShape &circle);

    // point and triangle
    static bool collides(const Vector3 &point, const Triangle &triangle);
};

} // namespace gamelib2
