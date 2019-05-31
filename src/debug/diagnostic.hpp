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

#include "joystick.hpp"
#include "../game/entity.hpp"
#include "../game/game.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>

#include <deque>

namespace gamelib2 {
class Diagnostic {
 public:
  Diagnostic(Game &in_game);
  virtual ~Diagnostic();
  static void active(bool status);
  static bool active();
  virtual void update();
  void render();
  virtual void selectEntity(Entity *e);
  virtual void deSelect() = 0;
  virtual void onClose();

  std::deque<float> fps_history;

  Joystick joystick1;

 protected:
  Game &game;
  static bool on;
  static bool inited;
  Entity *selected_entity = nullptr;
  int active_entity_index = 0;

  void process_entity_list(std::vector<const char *> &out_list,
                           std::vector<Entity *> &out_pointers,
                           int &out_active_index);

  sf::FloatRect panel_dimensions;
  sf::FloatRect last_panel_dimensions;

  float shown_fps = 0;
  float fps_min = 1000;
  float fps_max = 0;
  int frame_count = 0;
  sf::Clock ui_clock;
};

}  // namespace gamelib2
