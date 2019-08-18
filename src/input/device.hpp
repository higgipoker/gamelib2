#pragma once

#include <SFML/System/Clock.hpp>
#include <cstring>
#include <memory>
#include <set>
#include "input.hpp"

namespace gamelib2 {

/**
 * @brief The ControllerEventID enum
 */
enum ControllerEventID {
  NoEvent = 0,
  Fire,
  FireTap,
  DPadLeft,
  DPadRight,
  DPadUp,
  DPadDown
};

/**
 * @brief The ControllerEventStatus enum
 */
enum ControllerEventStatus { Released = 0, Pressed };

/**
 * @brief The ControllerEvent struct
 */
struct ControllerEvent {
  /**
   * @brief ControllerEvent
   */
  ControllerEvent() {
    id = NoEvent;
    status = Released;
    param = 0;
  }

  /**
   * @brief ControllerEvent
   * @param i
   * @param s
   * @param p
   */
  ControllerEvent(ControllerEventID i, ControllerEventStatus s, int p = 0) {
    id = i;
    status = s;
    param = p;
  }

  ControllerEventID id;
  ControllerEventStatus status;
  int param;
};

/**
 * @brief The ControllerListener class
 */
class ControllerListener {
 public:
  virtual ~ControllerListener() = default;

  /**
   * @brief onControllerEvent
   * @param event
   */
  virtual void onControllerEvent(ControllerEvent event) = 0;
};

/**
 * @brief The Controller class
 */
class Controller {
 public:
  /**
   * @brief Controller
   * @param i
   */
  Controller(InputDevice &i);
  virtual ~Controller() = default;

  /**
   * @brief update
   */
  virtual void update();

  /**
   * @brief setListener
   * @param l
   */
  void setListener(ControllerListener *l);
  int fire_ticks = 0;
  InputDevice &input;

 protected:
  ControllerListener *listener = nullptr;
  bool wait_for_release = false;

  /**
   * @brief notify
   * @param event
   */
  void notify(ControllerEvent event);

  static const int fire_tap_length = 15;
};
}  // namespace gamelib2
