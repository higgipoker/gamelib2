#include "collisions.hpp"
#include "../math/vector.hpp"

namespace gamelib2 {

// -----------------------------------------------------------------------------
// circle with circle
// -----------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------
// point with circle
// -----------------------------------------------------------------------------
bool Collision::collides(const Vector3 &point, const sf::CircleShape &circle) {
    auto c = circle.getPosition();
    if (((point.x - c.x) * (point.x - c.x) +
         (point.y - c.y) * (point.y - c.y)) <=
        (circle.getRadius() * circle.getRadius())) {
        return true;
    }

    return false;
}

// -----------------------------------------------------------------------------
// point with triangle
//
// the Barycentric Technique using dot products to cleverly avoid roots...
// see: http://www.blackpawn.com/texts/pointinpoly/default.html
// -----------------------------------------------------------------------------
bool Collision::collides(const Vector3 &point, const Triangle &triangle) {
    Vector3 v0 = Vector3(triangle.p3.x, triangle.p3.y) -
      Vector3(triangle.p1.x, triangle.p1.y);
    Vector3 v1 = Vector3(triangle.p2.x, triangle.p2.y) -
      Vector3(triangle.p1.x, triangle.p1.y);
    Vector3 v2 =
      Vector3(point.x, point.y) - Vector3(triangle.p1.x, triangle.p1.y);

    float dot00 = v0 * v0;
    float dot01 = v0 * v1;
    float dot02 = v0 * v2;
    float dot11 = v1 * v1;
    float dot12 = v1 * v2;

    float inv_denom = 1 / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * inv_denom;
    float v = (dot00 * dot12 - dot01 * dot02) * inv_denom;

    return (u >= 0) && (v >= 0) && (u + v < 1);
}

} // namespace gamelib2
