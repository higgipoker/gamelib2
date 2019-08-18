#pragma once

#include <string>
#include "../input/device.hpp"

namespace gamelib2 {

/**
 * @brief The State class
 */
class State {
 public:
  /**
   * @brief State
   */
  State();

  /**
   * @brief ~State
   */
  virtual ~State();

  /**
   * @brief start
   */
  virtual void start() = 0;

  /**
   * @brief update
   * @param dt
   */
  virtual void update(const float dt) = 0;

  /**
   * @brief end
   */
  virtual void end() = 0;

  /**
   * @brief finished
   * @return
   */
  virtual bool finished() = 0;

  /**
   * @brief changeToNextState
   */
  virtual void changeToNextState() = 0;

  /**
   * @brief handle_input
   * @param event
   */
  virtual void handle_input(const ControllerEvent &event) = 0;

  // identifier
  std::string name;
};
}  // namespace gamelib2
