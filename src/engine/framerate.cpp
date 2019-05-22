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
#include "framerate.hpp"
#include <iostream>
namespace gamelib2 {

void FrameRateManager::calc_fps() {
  ++frames_this_second;

  float elapsed_time = gamestep_timer.GetLiveTime() - lastTime;

  if (elapsed_time >= 1000) {
    fps = frames_this_second + 1;
    frames_this_second = 0;
    lastTime = gamestep_timer.GetLiveTime();
  }
}
void FrameRateManager::limit_framerate(float target_frame_time) {
  float newnewtime = gamestep_timer.GetLiveTime();
  float gametime = gamestep_timer.GetFrameTime();
  float frame_time = newnewtime - gametime;
  float target = (target_frame_time * 1000);
  while (frame_time < target - 1) {
    frame_time = gamestep_timer.GetLiveTime() - gametime;
  }
}
}  // namespace gamelib2
