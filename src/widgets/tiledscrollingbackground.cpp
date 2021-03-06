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
#include "tiledscrollingbackground.hpp"
#include <iostream>

namespace gamelib2 {

// -----------------------------------------------------------------------------
// TiledScrollingBackground
// -----------------------------------------------------------------------------
TiledScrollingBackground::TiledScrollingBackground(const std::string &in_file,
                                                   Camera &c)
    : Widget(in_file), camera(c) {
  init(in_file);
  clickable = true;
}

// -----------------------------------------------------------------------------
// init
// -----------------------------------------------------------------------------
void TiledScrollingBackground::init(const std::string &a_filename) {
  texture.Initialize(a_filename);
  sprite.setTexture(texture());
  total_width = 10000;
  total_height = 10000;

  tiles_wide =
      (total_width / static_cast<unsigned int>(sprite.getTextureRect().width)) +
      1;
  tiles_high = (total_height /
                static_cast<unsigned int>(sprite.getTextureRect().height)) +
               1;

  tile_width = static_cast<unsigned int>(sprite.getTextureRect().width);
  tile_height = static_cast<unsigned int>(sprite.getTextureRect().height);

  boundsrect.left = static_cast<float>(boundsrect.top = 0);
  boundsrect.width = static_cast<float>(tiles_wide * tile_width);
  boundsrect.height = static_cast<float>(tiles_high * tile_height);
}

// -----------------------------------------------------------------------------
// render
// -----------------------------------------------------------------------------
void TiledScrollingBackground::render(sf::RenderTarget &target) {
  for (unsigned int x = 0; x <= tiles_wide; x++) {
    for (unsigned int y = 0; y <= tiles_high; y++) {
      // get the absolute position of the tile
      sf::Rect<float> tile_rect(static_cast<float>(x * tile_width),
                                static_cast<float>(y * tile_height),
                                static_cast<float>(tile_width),
                                static_cast<float>(tile_height));

      sf::Rect<float> rect;
      rect.left = rect.top = 0;
      rect.width = target.getView().getSize().x;
      rect.height = target.getView().getSize().y;

      if (camera.getViewInWorld().intersects(tile_rect)) {
        sprite.setPosition(tile_rect.left + boundsrect.left,
                           tile_rect.top + boundsrect.top);
        target.draw(sprite);
      }
    }
  }
  boundsrect.width =
      (target.getView().getSize().x / tile_width + 1) * tile_width;
  boundsrect.height =
      (target.getView().getSize().y / tile_height + 1) * tile_height;
}

// -----------------------------------------------------------------------------
// bounds
// -----------------------------------------------------------------------------
sf::FloatRect TiledScrollingBackground::bounds() { return boundsrect; }

// -----------------------------------------------------------------------------
// setPosition
// -----------------------------------------------------------------------------
void TiledScrollingBackground::setPosition(float x, float y) {
  float dx = x - this->position().x;
  float dy = y - this->position().y;
  boundsrect.left = x;
  boundsrect.top = y;
  Widget::move(dx, dy);
}

// -----------------------------------------------------------------------------
// move
// -----------------------------------------------------------------------------
void TiledScrollingBackground::move(float dx, float dy) {
  boundsrect.left += dx;
  boundsrect.top += dy;
  Widget::move(dx, dy);
}

// -----------------------------------------------------------------------------
// position
// -----------------------------------------------------------------------------
sf::Vector2f TiledScrollingBackground::position() {
  return {boundsrect.left, boundsrect.top};
}
}  // namespace gamelib2
