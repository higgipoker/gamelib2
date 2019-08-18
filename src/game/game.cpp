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
#include "game.hpp"
#include <algorithm>
#include <iostream>

namespace gamelib2 {

const float target_frame_time = 1.0f / 60.0f;

// -----------------------------------------------------------------------------
// Game
// -----------------------------------------------------------------------------
Game::Game() {
  framerate_manager.OnFrameStarted();
  viewer.connectEngine(engine);
  camera.create("camera", "default camera");
  engine.addEntity(&camera);
  viewer.configWindow("Game", 800, 600, &camera);
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Game::update() {
  framerate_manager.OnFrameStarted();

  // render frame
  viewer.frame();

  // physics frame
  while (framerate_manager.TimeLeft(target_frame_time) >= 0) {
    engine.frame(timestep);
  }
}

// -----------------------------------------------------------------------------
// connect
// -----------------------------------------------------------------------------
void Game::connect(Entity *entity, Widget *widget) {
  entity->connectWidget(widget);
  widget->connectEntity(entity);
}

}  // namespace gamelib2
