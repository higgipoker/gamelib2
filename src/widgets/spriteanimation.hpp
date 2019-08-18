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
  /**
   * @brief SpriteAnimation
   * @param a_id
   * @param a_frametime
   * @param a_loop
   * @param a_frames
   * @param in_widget
   */
  SpriteAnimation(std::string a_id, float a_frametime, bool a_loop,
                  std::vector<int> a_frames, Sprite* in_widget = nullptr);

  /**
   * @brief connectSprite
   * @param in_sprite
   */
  void connectSprite(Sprite* in_sprite);

  /**
   * @brief start
   */
  void start();

  /**
   * @brief update
   * @param in_dt
   * @return
   */
  int update(float in_dt);

  /**
   * @brief stop
   */
  void stop();

  /**
   * @brief setStpeed
   * @param a_seped
   */
  void setStpeed(int a_seped);

  /**
   * @brief currentFrame
   * @return
   */
  int currentFrame();

  /**
   * @brief finished
   * @return
   */
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
