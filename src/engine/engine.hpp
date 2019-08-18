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
#include "../game/entity.hpp"
#include "../types.hpp"
#include "../viewer/viewer.hpp"
#include "../widgets/widget.hpp"
#include "framerate.hpp"

namespace gamelib2 {

class Viewer;
class Engine {
 public:
  /**
   * @brief frame
   * @param dt
   */
  void frame(float dt);

  /**
   * @brief addEntity
   * @param in_entity
   */
  void addEntity(Entity *in_entity);

  /**
   * @brief remEntity
   * @param in_entity
   */
  void remEntity(Entity *in_entity);

  /**
   * @brief paused
   */
  bool paused = false;

  /**
   * @brief fps
   */
  float fps = 0;

  /**
   * @brief entities
   */
  EntityList entities;

  // track current fram count
  int frame_count = 0;
};
}  // namespace gamelib2
