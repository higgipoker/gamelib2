#include "spriteanimation.hpp"

#include <iostream>

namespace gamelib2 {

// -----------------------------------------------------------------------------
// SpriteAnimation
// -----------------------------------------------------------------------------
SpriteAnimation::SpriteAnimation(std::string a_id, float a_frametime,
                                 bool a_loop, std::vector<int> a_frames,
                                 Sprite *in_widget)
    : name(std::move(a_id)),
      frames(std::move(std::move(a_frames))),
      current_frame(frames.begin()),
      loop(a_loop),
      frame_time(a_frametime),
      sprite(in_widget) {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SpriteAnimation::connectSprite(Sprite *in_sprite) { sprite = in_sprite; }

// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void SpriteAnimation::start() {
  current_frame = frames.begin();
  counter = 0;
  running = true;
}

// -----------------------------------------------------------------------------
// step
// -----------------------------------------------------------------------------
int SpriteAnimation::update(float in_dt) {
  if (running) {
    counter += in_dt;
    if (counter > frame_time) {
      counter = 0;

      if (++current_frame == frames.end()) {
        if (loop) {
          current_frame = frames.begin();
        } else {
          running = false;
          --current_frame;
        }
      }
    }
    if (sprite) {
      sprite->setFrame(*current_frame);
    }
  }
  return *current_frame;
}

// -----------------------------------------------------------------------------
// stop
// -----------------------------------------------------------------------------
void SpriteAnimation::stop() { running = false; }

// -----------------------------------------------------------------------------
// setStpeed
// -----------------------------------------------------------------------------
void SpriteAnimation::setStpeed(int a_speed) { frame_time = static_cast<float>(a_speed); }

// -----------------------------------------------------------------------------
// currentFrame
// -----------------------------------------------------------------------------
int SpriteAnimation::currentFrame() { return *current_frame; }

// -----------------------------------------------------------------------------
// finished
// -----------------------------------------------------------------------------
bool SpriteAnimation::finished() {
  if (!loop) {
    return !running;
  }
  return false;
}

}  // namespace gamelib2
