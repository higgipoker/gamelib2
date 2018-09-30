#include "collisions.hpp"
#include "../math/vector.hpp"

namespace gamelib2 {

bool Collision::collides(const sf::CircleShape &c1, const sf::CircleShape &c2) {

    if (Floats::equal(c1.getRadius(), 0) || Floats::equal(c2.getRadius(), 0)) {
        return false;
    }

    // compare the distance to combined radii
    float dx = c2.getPosition().x - c1.getPosition().x;
    float dy = c2.getPosition().y - c1.getPosition().y;
    float radii = c1.getRadius() + c2.getRadius();

    if ((dx * dx) + (dy * dy) < radii * radii) {
        return true;
    }

    return false;
}

} // namespace gamelib2
