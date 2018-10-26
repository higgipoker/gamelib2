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

namespace gamelib2 {

bool Diagnostic::on = false;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Diagnostic::Diagnostic(Viewer &v) : viewer(v) {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Diagnostic::update() {
  // ImGui::ShowDemoWindow();

  if (selected_entity == nullptr) {
    selectEntity(viewer.engine->entities[0]);
  }

  // global debug window
  ImGui::Begin("Debug");

  // fps
  ImGui::Text("FPS: %i", static_cast<int>(viewer.fps));

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
} // namespace gamelib2
