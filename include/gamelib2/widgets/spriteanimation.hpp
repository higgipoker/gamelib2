#pragma once

#include "sprite.hpp"

#include <string>
#include <vector>

namespace gamelib2 {

/**
 * @brief a sprite animatio is just a lst of frames and a speed
 */
class SpriteAnimation {
 public:
  SpriteAnimation(std::string a_id, float a_frametime, bool a_loop,
                  std::vector<int> a_frames, Sprite* in_widget = nullptr);

  // set the sprite to operate on
  void connectSprite(Sprite* in_sprite);

  // start the animation
  void start();

  // update anim
  int update(float in_dt);

  // stop animation
  void stop();

  // set the frame update speed
  void setStpeed(int a_seped);

  // get the current frame
  int currentFrame();

  // for non looping animations, is finished?
  bool finished();

  std::string name;

 private:
  // the sprite to operate on
  Sprite* sprite = nullptr;

  // list of frame numbers
  std::vector<int> frames;

  // point to current frame
  std::vector<int>::iterator current_frame;

  // is a looping animation
  bool loop = false;

  // animation is still running
  bool running = false;

  // time of a frame
  float frame_time = 0;

  // frame timer
  float counter = 0;
};
}  // namespace gamelib2
