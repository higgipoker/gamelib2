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
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>
#include <deque>

namespace gamelib2 {
class viewer;
class Diagnostic {
public:
  Diagnostic(std::shared_ptr<Viewer> &v);
  virtual ~Diagnostic() = default;
  static void active(bool status);
  static bool active();
  virtual void update();
  void render();
  virtual void selectEntity(std::weak_ptr<Entity> e);
  virtual void deSelect() = 0;
  virtual void onClose() = 0;

  std::deque<float> fps_history;

protected:
  std::weak_ptr<Viewer> viewer;
  static bool on;
  static bool inited;
  std::weak_ptr<Entity> selected_entity;
  unsigned int active_entity_index = 0;

  void process_entity_list(std::vector<const char *> &out_list,
                           std::vector<std::weak_ptr<Entity> > &out_pointers,
                           int &out_active_index);

  sf::FloatRect panel_dimensions;
  sf::FloatRect last_panel_dimensions;

  float shown_fps = 0;
  float fps_min=1000;
  float fps_max = 0;
  int frame_count=0;
  sf::Clock ui_clock;
};

} // namespace gamelib2
