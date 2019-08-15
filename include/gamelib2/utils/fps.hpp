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
  static int getFPS() { return mFps; }

 private:
  static int mFrame;
  static int mFps;
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
int FPS::mFrame = 0;
int FPS::mFps = 0;
sf::Clock FPS::mClock;
}  // namespace gamelib2
#endif  // FPS_HPP
