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
#include "entity.hpp"
#include <iostream>
#include "../widgets/widget.hpp"

namespace gamelib2 {

Entity::Entity() {}
// -----------------------------------------------------------------------------
// create
// -----------------------------------------------------------------------------
void Entity::create(const std::string &in_type, const std::string &in_name) {
  type = in_type;
  name = in_name;
}

// -----------------------------------------------------------------------------
// connectWidget
// -----------------------------------------------------------------------------
void Entity::connectWidget(Widget *in_widget) { widget = in_widget; }

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Entity::update(float dt) {
  // differnt types of enteties can override this to do movement physics or
  // whatever
  widget->z_order = static_cast<int>(position.y);

  if (widget) {
    // reset the debug primitives
    widget->shapes.clear();
    widget->primitives.clear();
  }
}

// -----------------------------------------------------------------------------
// perspectivize
// -----------------------------------------------------------------------------
void Entity::perspectivize(float camera_height) {}

// -----------------------------------------------------------------------------
// on_moved
// -----------------------------------------------------------------------------
void Entity::onDragged(const Vector3 &diff) { position += diff; }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Entity::setPosition(float x, float y) {
  position.x = x;
  position.y = y;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Entity::setPosition(const Vector3 &pos) { position = pos; }
}  // namespace gamelib2
