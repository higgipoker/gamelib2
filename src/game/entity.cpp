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
void Entity::connectWidget(WidgetPtrWeak &in_widget) {
    widget = in_widget;
}

// -----------------------------------------------------------------------------
// releaseWidget
// -----------------------------------------------------------------------------
void Entity::releaseWidget() {
    widget.reset();
}

// -----------------------------------------------------------------------------
// connectKeyboard
// -----------------------------------------------------------------------------
void Entity::connectKeyboard(KeyboardPtrWeak &in_keyboard) {
    keyboard = in_keyboard;
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Entity::update(float dt) {
    // differnt types of enteties can override this to do movement physics or
    // whatever

    handle_input();
}

// -----------------------------------------------------------------------------
// handle_input
// -----------------------------------------------------------------------------
void Entity::handle_input() {
    auto kb = keyboard.lock();
    if (kb.get() == nullptr)
        return;

    velocity.reset();

    if (kb->event_states[UP]) {
        velocity.y = -1;
    }

    if (kb->event_states[RIGHT]) {
        velocity.x = 1;
    }

    if (kb->event_states[DOWN]) {
        velocity.y = 1;
    }

    if (kb->event_states[LEFT]) {
        velocity.x = -1;
    }
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
void Entity::onMoved(const Vector3 &new_position, float dx, float dy) {
    position.x = new_position.x;
    position.y = new_position.y;
}
} // namespace gamelib2
