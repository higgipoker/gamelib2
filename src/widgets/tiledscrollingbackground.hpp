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
#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include "../camera/camera.hpp"
#include "../graphics/autotexture.hpp"
#include "../widgets/widget.hpp"

namespace gamelib2 {

/**
 * @brief The TiledScrollingBackground class
 */
class TiledScrollingBackground : public Widget {
 public:
  /**
   * @brief TiledScrollingBackground
   * @param in_file
   * @param c
   */
  TiledScrollingBackground(const std::string &in_file, Camera &c);

  /**
   * @brief init
   * @param a_filename
   */
  void init(const std::string &a_filename);

  // since a scrolling bg can be subclassed and draw extra stuff,
  // this has to be pure so the derived class draw children
  // AFTER any extra stuff they drew on top of the bg
  // (eg the lines on a football pitch)

  /**
   * @brief render
   * @param target
   */
  void render(sf::RenderTarget &target) override = 0;

  /**
   * @brief bounds
   * @return
   */
  sf::FloatRect bounds() override;

  /**
   * @brief setPosition
   * @param x
   * @param y
   */
  void setPosition(float x, float y) override;

  /**
   * @brief move
   * @param dx
   * @param dy
   */
  void move(float dx, float dy) override;

  /**
   * @brief position
   * @return
   */
  sf::Vector2f position() override;

 private:
  sf::FloatRect boundsrect;
  unsigned int total_width = 0, total_height = 0;
  unsigned int tile_width = 0, tile_height = 0;
  unsigned int tiles_wide = 0, tiles_high = 0;

  sf::Sprite sprite;
  AutoTexture texture;

  // pitch is a special type of widget, needs camera
  Camera &camera;
};

}  // namespace gamelib2
