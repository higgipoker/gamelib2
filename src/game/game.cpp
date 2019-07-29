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

const float target_frame_time = 1.f / 60.f;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Game::Game() {
  framerate_manager.gamestep_timer.Start();
  viewer.configWindow("Game", 800, 600);
  viewer.connectEngine(engine);
  camera.create("camera", "default camera");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Game::update() {
  on_frame_start();

   // render frame
  if (!engine.paused) {
    camera.update(timestep);
  }
  viewer.setView(camera.view);
  viewer.frame();

  // physics frame
  do{engine.frame(timestep);
  }while (framerate_manager.limit_framerate(target_frame_time));

 
  on_frame_end();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Game::on_frame_start() { framerate_manager.gamestep_timer.Update(); }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Game::on_frame_end() { framerate_manager.calc_fps(); }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Game::addSprite(const GameSprite &in_gamesprite) {
  viewer.addWidget(in_gamesprite.sprite);
  viewer.addWidget(in_gamesprite.shadow);
}

}  // namespace gamelib2
