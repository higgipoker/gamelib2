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
#include "../utils/timer.hpp"
#include "../viewer/viewer.hpp"
#include <cassert>
#include <iostream>

namespace gamelib2 {

// static float accumulator = 0.0f;
static float target_frame_time = 1.f / 60.f;

// -----------------------------------------------------------------------------
// Engine
// -----------------------------------------------------------------------------
Engine::Engine() = default;

// -----------------------------------------------------------------------------
// ~Engine
// -----------------------------------------------------------------------------
Engine::~Engine() {
    entities.clear();
}

// -----------------------------------------------------------------------------
// run
// -----------------------------------------------------------------------------
void Engine::frame(float dt) {
    if (paused)
        return;
    framerate_manager.gamestep_timer.Update();

    for (auto &entity : entities) {
        entity->update(dt);
    }

    ++frame_count;
    framerate_manager.calc_fps();
    framerate_manager.limit_framerate(target_frame_time);
    fps = framerate_manager.fps;
}

// -----------------------------------------------------------------------------
// connectViewer
// -----------------------------------------------------------------------------
void Engine::connectViewer(Viewer *in_viewer) {
    assert(in_viewer != nullptr);
    viewer = in_viewer;
    viewer->onMessage("connected");
}

// -----------------------------------------------------------------------------
// addEntity
// -----------------------------------------------------------------------------
void Engine::addEntity(EntityPtr &in_entity) {
    entities.emplace_back(in_entity);
}

// -----------------------------------------------------------------------------
// addEntity
// -----------------------------------------------------------------------------
void Engine::remEntity(EntityPtr &in_entity) {
    // entities.emplace_back(in_entity);
}

// -----------------------------------------------------------------------------
// onMessage
// -----------------------------------------------------------------------------
void Engine::onMessage(const std::string &in_msg) {
    std::cout << "Message from viewer: " << in_msg << std::endl;
}

} // namespace gamelib2
