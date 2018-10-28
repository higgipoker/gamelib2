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
#include "diagnostic.hpp"
#include "../engine/engine.hpp"
#include "../viewer/viewer.hpp"
#include "../widgets/widget.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include <iostream>

namespace gamelib2 {

bool Diagnostic::on = false;
bool Diagnostic::inited = false;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Diagnostic::Diagnostic(Viewer &v) : viewer(v) {
  panel_dimensions.left = 0;
  panel_dimensions.top = 0;
  panel_dimensions.width = 0;
  panel_dimensions.height = 0;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Diagnostic::update() {
  inited = true;
  ImGui::SFML::Update(viewer.getWindow(), ui_clock.restart());
  // ImGui::ShowDemoWindow();

  // dimensions
  panel_dimensions.width = viewer.getWindow().getSize().x / 3.2f;
  panel_dimensions.height = viewer.getWindow().getSize().y / 5;
  panel_dimensions.left =
      viewer.getWindow().getSize().x - panel_dimensions.width;
  panel_dimensions.top = 0;

  ImGui::SetNextWindowSize(
      sf::Vector2f(panel_dimensions.width, panel_dimensions.height));
  ImGui::SetNextWindowPos(
      sf::Vector2f(panel_dimensions.left, panel_dimensions.top));

  if (selected_entity == nullptr) {
    selectEntity(viewer.engine->entities[0]);
  }

  // global debug window
  ImGui::Begin("Debug");

  // fps
  if (viewer.engine->frame_count % 100 == 0) {
    shown_fps = viewer.fps;
  }
  ImGui::Text("FPS: %i", static_cast<int>(shown_fps));

  { // entities
    int active_entity_index = 0;
    std::vector<Entity *> entity_pointers;
    std::vector<const char *> entities;
    process_entity_list(entities, entity_pointers, active_entity_index);
    ImGui::Combo("Entities", &active_entity_index, entities.data(),
                 entities.size());
    if (selected_entity) {
      if (selected_entity->name != entities[active_entity_index]) {
        selectEntity(entity_pointers[active_entity_index]);
      }
    }
  }

  last_panel_dimensions = panel_dimensions;
  ImGui::End();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Diagnostic::selectEntity(Entity *e) { selected_entity = e; }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Diagnostic::active(bool status) {
  on = status;
  Widget::debug = on;

  if (!on) {
    inited = false;
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool Diagnostic::active() { return on; }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Diagnostic::process_entity_list(std::vector<const char *> &out_list,
                                     std::vector<Entity *> &out_pointers,
                                     int &out_active_index) {

  int idx = 0;
  for (auto &entity : viewer.engine->entities) {
    out_list.emplace_back(entity->name.c_str());
    out_pointers.emplace_back(entity);
    if (selected_entity == entity) {
      out_active_index = idx;
    }
    idx++;
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Diagnostic::render() {
  if (inited) {
    ImGui::SFML::Render(viewer.getWindow());
  }
}
} // namespace gamelib2
