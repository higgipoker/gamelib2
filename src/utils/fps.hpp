#ifndef FPS_HPP
#define FPS_HPP
#include <SFML/System.hpp>
namespace gamelib2 {

class FPS {
 public:
  /// @brief Constructor with initialization.
  ///
  FPS() {}

  /// @brief Update the frame count.
  ///

  /// @brief Get the current FPS count.
  /// @return FPS count.
  static unsigned int getFPS() { return mFps; }

 private:
  static unsigned int mFrame;
  static unsigned int mFps;
  static sf::Clock mClock;

 public:
  static void update() {
    if (mClock.getElapsedTime().asSeconds() >= 1.f) {
      mFps = mFrame;
      mFrame = 0;
      mClock.restart();
    }

    ++mFrame;
  }
};
unsigned int FPS::mFrame = 0;
unsigned int FPS::mFps = 0;
sf::Clock FPS::mClock;
}  // namespace gamelib2
#endif  // FPS_HPP
