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

#include "../game/entity.hpp"
#include "../game/game.hpp"
#include "joystick.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>

#include <deque>

namespace gamelib2 {
class Diagnostic {
 public:
  /**
   * @brief Diagnostic
   * @param in_game
   */
  Diagnostic(Game &in_game);

  /**
   * @brief ~Diagnostic
   */
  virtual ~Diagnostic();

  /**
   * @brief active
   * @param status
   */
  static void active(bool status);

  /**
   * @brief active
   * @return
   */
  static bool active();

  /**
   * @brief update
   */
  virtual void update();

  /**
   * @brief render
   */
  void render();

  /**
   * @brief selectEntity
   * @param e
   */
  virtual void selectEntity(Entity *e);

  /**
   * @brief deSelect
   */
  virtual void deSelect() = 0;

  /**
   * @brief onClose
   */
  virtual void onClose();

  // data for fps display
  std::deque<float> fps_history;

  // a debug joystick display
  Joystick joystick1;

 protected:
  // reference to game to access entities
  Game &game;

  // status
  static bool on;

  // inited flag
  static bool inited;

  // selected entity
  Entity *selected_entity = nullptr;

  // save index for list item
  int active_entity_index = 0;

  /**
   * @brief process_entity_list
   * @param out_list
   * @param out_pointers
   * @param out_active_index
   */
  void process_entity_list(std::vector<const char *> &out_list,
                           std::vector<Entity *> &out_pointers,
                           int &out_active_index);

  // dimensions
  sf::FloatRect panel_dimensions;

  // widget data
  float shown_fps = 0;
  float fps_min = 1000;
  float fps_max = 0;
  int frame_count = 0;
  sf::Clock ui_clock;
};

}  // namespace gamelib2
