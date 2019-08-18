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
#include <cstring>
namespace gamelib2 {

/**
 * @brief The InputState enum
 */
enum InputState {
  Up = 0,
  Down,
  Left,
  Right,

  FireDown,
  FireUp,
  FireLength,
  FireLengthCached,
  SingleTap,
  DoubleTap,
  FirePress,

  FireDown2,
  FireUp2,
  FireLength2,
  FireLengthCached2,
  SingleTap2,
  DoubleTap2,
  FirePress2,

  FireDown3,
  FireUp3,
  FireLength3,
  FireLengthCached3,
  SingleTap3,
  DoubleTap3,
  FirePress3,

  FireDown4,
  FireUp4,
  FireLength4,
  FireLengthCached4,
  SingleTap4,
  DoubleTap4,
  FirePress4,

  Totalevents
};

/**
 * @brief The InputDevice class
 */
class InputDevice {
 public:
  InputDevice() = default;
  virtual ~InputDevice() = default;

  /**
   * @brief update
   */
  virtual void update() = 0;

  /**
   * @brief reset
   */
  void reset() { memset(states, 0, sizeof(states)); }

  /// input states
  int states[InputState::Totalevents]{};

 protected:
  /// count fire ticks
  int fire_ticks = 0;
};

}  // namespace gamelib2
