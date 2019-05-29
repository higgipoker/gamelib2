/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
#include "primitives.hpp"
#include "../math/vector.hpp"

namespace gamelib2 {

// -----------------------------------------------------------------------------
// drawLine
// -----------------------------------------------------------------------------
void Primitives::drawLine(sf::RenderTarget &target, const Vector3 &point1,
                          const Vector3 &point2, int thickness) {
  sf::Vertex vertices[4];
  Vector3 direction = point2 - point1;
  Vector3 unit_direction = direction / std::sqrt(direction.x * direction.x +
                                                 direction.y * direction.y);
  Vector3 unit_perpendicular(-unit_direction.y, unit_direction.x);

  Vector3 offset = unit_perpendicular * (thickness / 2.f);

  Vector3 tmp1 = point1 + offset;
  Vector3 tmp2 = point2 + offset;
  Vector3 tmp3 = point2 - offset;
  Vector3 tmp4 = point1 - offset;

  vertices[0].position.x = tmp1.x;
  vertices[0].position.y = tmp1.y;

  vertices[1].position.x = tmp2.x;
  vertices[1].position.y = tmp2.y;

  vertices[2].position.x = tmp3.x;
  vertices[2].position.y = tmp3.y;

  vertices[3].position.x = tmp4.x;
  vertices[3].position.y = tmp4.y;

  for (int i = 0; i < 4; ++i) {
    vertices[i].color = sf::Color(255, 255, 255, 255);
  }

  target.draw(vertices, 4, sf::Quads);
}

// -----------------------------------------------------------------------------
// Arc
// -----------------------------------------------------------------------------
void Primitives::arc(sf::RenderTarget &target, float x, float y, float radius,
                     float start, float end, int segments,
                     int thickness) {

  // construct the vertex list
  std::vector<sf::Vertex> vertices;

  // trackers
  float act_start = start;
  float act_end = end;

  float lastx = 0;
  float lasty = 0;

  for (int i = 0; i < thickness; ++i) {
    float current = act_start;
    int segments_drawn = 0;

    while (current <= act_end) {
      float ax = x + radius * cosf(RADIANS(current));
      float ay = y + radius * sinf(RADIANS(current));
      current += ((act_end - act_start) / segments);

      vertices.push_back(
          sf::Vertex(sf::Vector2f(ax, ay), sf::Color(255, 255, 255, 255)));

      if (segments_drawn) {
        drawLine(target, Vector3(lastx, lasty), Vector3(ax, ay), thickness);
      }

      lastx = ax;
      lasty = ay;

      ++segments_drawn;
    }

    radius += 0.2f;
    act_start = start;
    act_end = end;
  }

  // draw vertex list
  target.draw(&vertices[0], vertices.size(), sf::LinesStrip);
}

} // namespace gamelib2
