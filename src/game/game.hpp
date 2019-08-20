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
#include "../camera/camera.hpp"
#include "../engine/engine.hpp"
#include "../viewer/viewer.hpp"
#include "../widgets/widget.hpp"
#include "entity.hpp"

namespace gamelib2 {
/**
 * @brief The Game class
 */
class Game {
 public:
  /**
   * @brief Game
   */
  Game();

  /**
   * @brief update
   */
  virtual void update();

  /**
   * @brief connect
   * @param entity
   * @param widget
   */
  static void connect(Entity *entity, Widget *widget);

  // game engine
  Engine engine;

  // game viewer
  Viewer viewer;

  // game camera
  Camera camera;

 protected:
  // physics time delta
  const float timestep = 0.01f;

  // a frame rate manager
  FrameRateManager framerate_manager;

  // friend for debug
  friend class Diagnostic;
};
}  // namespace gamelib2
