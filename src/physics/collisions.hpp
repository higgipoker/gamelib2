#pragma once
#include <SFML/Graphics/CircleShape.hpp>

namespace gamelib2 {

class Collision {
public:
    // circle and circle
    static bool collides(const sf::CircleShape &c1, const sf::CircleShape &c2);
};

} // namespace gamelib2
