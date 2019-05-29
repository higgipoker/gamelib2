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

#include <imgui-SFML.h>
#include <imgui.h>

#include <iostream>
#include <sstream>

namespace gamelib2 {

bool Diagnostic::on = false;
bool Diagnostic::inited = false;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Diagnostic::Diagnostic(Game &in_game) : game(in_game) {
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
  ImGui::SFML::Update(game.viewer.getWindow(), ui_clock.restart());
  // ImGui::ShowDemoWindow();

  // dimensions
  panel_dimensions.width = game.viewer.getWindow().getSize().x / 2.98f;
  panel_dimensions.height = game.viewer.getWindow().getSize().y / 4;
  panel_dimensions.left =
      game.viewer.getWindow().getSize().x - panel_dimensions.width;
  panel_dimensions.top = 0;

  ImGui::SetNextWindowSize(
      sf::Vector2f(panel_dimensions.width, panel_dimensions.height));
  ImGui::SetNextWindowPos(
      sf::Vector2f(panel_dimensions.left, panel_dimensions.top));

  if (selected_entity) {
    selectEntity(selected_entity);
  }

  // global debug window
  ImGui::Begin("Debug");

  {  // fps
    std::vector<float> values;
    int cnt = 0;
    fps_min = 1000;
    fps_max = 0;
    for (auto &val : fps_history) {
      values.push_back(val);
      cnt += val;
      if (val < fps_min) {
        fps_min = val;
      }
      if (val > fps_max) {
        fps_max = val;
      }
    }
    std::ostringstream title;
    title << values.back() << "FPS (past 1000 frames)";
    ImGui::Text("%i%s", static_cast<int>(values.back()), " FPS");
    float avg = static_cast<float>(cnt / values.size());
    std::ostringstream capt;
    ImGui::PlotLines("##fps", values.data(), static_cast<int>(values.size()), 0,
                     "(past 1000 frames)", avg - 6, avg + 15,
                     ImVec2(panel_dimensions.width, 50));
  }  // end fps

  {  // entities
    int active_entity_index = 0;
    std::vector<Entity *> entity_pointers;
    std::vector<const char *> entities;
    process_entity_list(entities, entity_pointers, active_entity_index);
    ImGui::Text("%i entities:", static_cast<int>(entities.size()));
    std::ostringstream e_capt;
    ImGui::Combo("##Entities", &active_entity_index, entities.data(),
                 static_cast<int>(entities.size()));
    if (selected_entity) {
      if (selected_entity->name !=
          entities[static_cast<unsigned long>(active_entity_index)]) {
        selectEntity(
            entity_pointers[static_cast<unsigned long>(active_entity_index)]);
      }
    }
  }  // end entities

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
  for (auto &entity : game.engine.entities) {
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
    ImGui::SFML::Render(game.viewer.getWindow());
  }
}
}  // namespace gamelib2
