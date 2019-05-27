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

class GameSprite {
 public:
  GameSprite(Widget *in_sprite, Widget *in_shadow)
      : sprite(in_sprite), shadow(in_shadow) {}

  Widget *sprite = nullptr;
  Widget *shadow = nullptr;
};

class Game {
 public:
  Game();

  void addSprite(const GameSprite &in_gamesprite);

  virtual void update();
  Engine engine;
  Viewer viewer;
  Camera camera;

  static void connect(Entity *entity, Widget *widget) {
    entity->connectWidget(widget);
    widget->connectEntity(entity);
  }

 protected:
  void on_frame_start();
  void on_frame_end();
  const float timestep = 0.01f;
  FrameRateManager framerate_manager;

  friend class Diagnostic;
};
}  // namespace gamelib2
