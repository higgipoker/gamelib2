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

// a debug interface that all entities must implement
class EntityInterface {
public:
    // the entity was manually moved
    virtual void onDragged(const Vector3 &diff) = 0;

protected:
};

class Entity : public EntityInterface {
public:
    // construct with a name id
    Entity(std::string in_name);
    virtual ~Entity();

    // a game entity is associated with a widget
    void connectWidget(std::unique_ptr<Widget> in_widget);

    // release the widget
    void releaseWidget();

    // after any initiliazations are done (eg connect to widget)
    virtual void activate();

    // main update
    virtual void update(float dt);

    // debug interface
    void onDragged(const Vector3 &diff) override;

    // movement speed
    float speed = 150.0f;

    // physical aspects
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;

    // identifier name
    std::string name;

    // entity is associated with a widget
    std::unique_ptr<Widget> widget;

protected:
    // optionally add perspective
    virtual void perspectivize(float camera_height);
};
} // namespace gamelib2
