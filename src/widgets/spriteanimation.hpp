#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

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
   */
  SpriteAnimation(std::string a_id, unsigned int a_frametime, bool a_loop,
                  std::vector<unsigned int> a_frames);

  /**
   * @brief start the animation
   */
  void start();

  /**
   * @brief step the animation
   */
  unsigned int step();

  /**
   * @brief stop the animation
   */
  void stop();

  /**
   * @brief set anim speed
   * @param a_seped number of ticks per anim frame
   */
  void setStpeed(unsigned int a_seped);

  /**
   * @brief currentFrame
   * @return
   */
  unsigned int currentFrame();

  /// a name to identify the animatin easily
  std::string name;

 private:
  /// list of frame numbers
  std::vector<unsigned int> frames;

  /// point to current frame
  std::vector<unsigned int>::iterator current_frame;

  /// is a looping animation
  bool loop = false;

  /// animation is still running
  bool running = false;

  /// time of a frame
  unsigned int frame_time = 0;

  /// frame timer
  unsigned int ticks = 0;
};
}  // namespace gamelib2
#endif  // SPRITEANIMATION_H
