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
#include "engine.hpp"
#include <cassert>
#include <iostream>
#include "../utils/timer.hpp"
#include "../viewer/viewer.hpp"

namespace gamelib2 {

// static float accumulator = 0.0f;

// -----------------------------------------------------------------------------
// run
// -----------------------------------------------------------------------------
void Engine::frame(float dt) {
  if (paused) dt = 0;

  for (auto &entity : entities) {
    entity->update(dt);
  }

  ++frame_count;
}

// -----------------------------------------------------------------------------
// addEntity
// -----------------------------------------------------------------------------
void Engine::addEntity(Entity *in_entity) {
 // assert(in_entity->widget != nullptr);
  entities.emplace_back(in_entity);
}

// -----------------------------------------------------------------------------
// addEntity
// -----------------------------------------------------------------------------
void Engine::remEntity(Entity *in_entity) {
  entities.erase(std::remove(entities.begin(), entities.end(), in_entity),
                 entities.end());
  ;
}

// -----------------------------------------------------------------------------
// onMessage
// -----------------------------------------------------------------------------
void Engine::onMessage(const std::string &in_msg) {
  std::cout << "Message from viewer: " << in_msg << std::endl;
}

}  // namespace gamelib2
