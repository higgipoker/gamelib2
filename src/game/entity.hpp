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
#include "../input/input.hpp"
#include "../input/keyboard.hpp"
#include "../math/vector.hpp"
#include "../types.hpp"
#include <map>
#include <string>

namespace gamelib2 {
class Widget;
class Entity {
public:
    // construct with a name id
    Entity(const std::string in_name);
    ~Entity();

    // a game entity is associated with a widget
    void connectWidget(WidgetPtrWeak &in_widget);

    // release the widget
    void releaseWidget();

    // connect to an input
    void connectKeyboard(KeyboardPtrWeak &in_keyboard);

    // after any initiliazations are done (eg connect to widget)
    virtual void activate();

    // main update
    virtual void update(float dt);

    // the entity was manually moved
    virtual void onMoved(const Vector3 &new_position,float dx=0, float dy=0);

    // movement speed
    float speed = 150.0f;

    // physical aspects
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;

    // identifier name
    std::string name;

    // entity is associated with a widget
    WidgetPtrWeak widget;

private:
    // handle input
    void handle_input();

    // optionally add perspective
    virtual void perspectivize(float camera_height);

    // an entity can handle input
    KeyboardPtrWeak keyboard;
};
} // namespace gamelib2
