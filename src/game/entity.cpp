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
  : name(in_name) {
}

// -----------------------------------------------------------------------------
// connectWidget
// -----------------------------------------------------------------------------
void Entity::connectWidget(WidgetPtr in_widget) {
    widget = in_widget;
}

// -----------------------------------------------------------------------------
// connectKeyboard
// -----------------------------------------------------------------------------
void Entity::connectKeyboard(std::shared_ptr<Keyboard> &in_keyboard) {
    keyboard = in_keyboard;
}

// -----------------------------------------------------------------------------
// update
// -----------------------------------------------------------------------------
void Entity::update(float dt) {

    // has the sprite been manually moved
    Vector3 wpos(widget->position().x, widget->position().y);
    if (!wpos.equals(position)) {
        position.x = widget->position().x;
        position.y = widget->position().y;
    }

    // handle inputs
    handle_input();

    // normalises to units
    velocity.normalise();

    // normalizes for diagonals
    if (velocity.magnitude() > running_speed) {
        velocity *= running_speed;
    }

    // basic euler motion
    velocity += acceleration * dt;
    position += velocity * dt * running_speed;
    acceleration.reset();

    // associated widget
    if (widget.get()) {
        widget->setPosition(position.x, position.y);
    }
    widget->animate();
}

// -----------------------------------------------------------------------------
// handle_input
// -----------------------------------------------------------------------------
void Entity::handle_input() {
    if (keyboard.get() == nullptr)
        return;

    velocity.reset();

    if (keyboard->event_states[UP]) {
        velocity.y = -1;
    }

    if (keyboard->event_states[RIGHT]) {
        velocity.x = 1;
    }

    if (keyboard->event_states[DOWN]) {
        velocity.y = 1;
    }

    if (keyboard->event_states[LEFT]) {
        velocity.x = -1;
    }
}
} // namespace gamelib2
