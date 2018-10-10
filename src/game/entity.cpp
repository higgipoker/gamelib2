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
#include "../widgets/widget.hpp"

namespace gamelib2 {

// -----------------------------------------------------------------------------
// Entity
// -----------------------------------------------------------------------------
Entity::Entity(const std::string in_name)
  : name(std::move(in_name)) {
}

// -----------------------------------------------------------------------------
// ~Entity
// -----------------------------------------------------------------------------
Entity::~Entity() {
}

// -----------------------------------------------------------------------------
// connectWidget
// -----------------------------------------------------------------------------
void Entity::connectWidget(std::unique_ptr<Widget> in_widget) {
    widget = std::move(in_widget);
}

// -----------------------------------------------------------------------------
// releaseWidget
// -----------------------------------------------------------------------------
void Entity::releaseWidget() {
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Entity::update(float dt) {
    // differnt types of enteties can override this to do movement physics or
    // whatever
}

// -----------------------------------------------------------------------------
// activate
// -----------------------------------------------------------------------------
void Entity::activate() {
}

// -----------------------------------------------------------------------------
// perspectivize
// -----------------------------------------------------------------------------
void Entity::perspectivize(float camera_height) {
}

// -----------------------------------------------------------------------------
// on_moved
// -----------------------------------------------------------------------------
void Entity::onDragged(const Vector3 &diff) {
    position += diff;
}
} // namespace gamelib2
