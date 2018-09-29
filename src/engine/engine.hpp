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

#include "../types.hpp"
#include "../utils/timer.hpp"

namespace gamelib2 {
class Viewer;
class Engine {
  public:
    Engine();

    // do one frame
    void frame(float dt);

    // connect to a viewer
    void connectViewer(Viewer *in_viewer);

    // add an entity to the engine
    void addEntity(EntityPtr &in_entity);

    // handle a message from the viewer (or anyone else actually)
    void onMessage(const std::string &in_msg);

    // we can pause the sim
    bool paused = false;

    // outside access to fps
    float fps = 0;

  private:
    // engine links to a viewer
    Viewer *viewer;

    // track current fram count
    unsigned int frame_count = 0;

    // list of entities
    EntityList entities;

    // fps stuff
    struct FrameRateManager {
        void calc_fps() {
            ++frames_this_second;

            float elapsed_time = gamestep_timer.GetLiveTime() - lastTime;

            if (elapsed_time >= 1000) {
                fps = frames_this_second + 1;
                frames_this_second = 0;
                lastTime = gamestep_timer.GetLiveTime();
            }
        }
        void limit_framerate(float target_frame_time) {
            float newnewtime = gamestep_timer.GetLiveTime();
            float gametime = gamestep_timer.GetFrameTime();
            float frame_time = newnewtime - gametime;
            float target = (target_frame_time * 1000);
            while (frame_time < target) {
                newnewtime = gamestep_timer.GetLiveTime();
                frame_time = newnewtime - gamestep_timer.GetFrameTime();
            }
        }
        Timer gamestep_timer;
        float fps = 0;
        float frames_this_second = 0;
        float lastTime = 0.0f;
        float fps_timer = 0.0f;
    } framerate_manager;
};
} // namespace gamelib2
