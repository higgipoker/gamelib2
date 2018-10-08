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
#include "../math/vector.hpp"
#include "../types.hpp"
#include "../widgets/spriteanimation.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <map>

namespace gamelib2 {

class Entity;
class Widget {
public:
    Widget();
    virtual ~Widget();

    // a widget is associated with an entity
    virtual void connectEntity(Entity *in_entity);

    // release the entity
    virtual void releaseEntity();

    // safely get the associated name
    std::string getName();

    // renders itself with sfml
    virtual void render(sf::RenderTarget &target);

    // add a child to the widget tree from here
    virtual void addChild(Widget *in_widget);

    // add an animation by pointer
    virtual void addAnimation(SpriteAnimation &a_sprite_anim);

    // add an animation by params
    virtual void addAnimation(const std::string &animname,
                              unsigned int frametime, bool loopanim,
                              std::vector<unsigned int> framelist);

    // start an animation
    virtual void startAnimation(const std::string &a_name);

    // stop an animation
    virtual void stopAnimation();

    // update the animation
    virtual void animate();

    // get currently active animation
    SpriteAnimation *currentAnimation();

    // move by an offset
    virtual void move(float dx, float dy);

    // move to an absolute position
    virtual void setPosition(float x, float y);

    // set scale
    virtual void scale(float x, float y);

    // get scale
    virtual float scale();

    // check if point is in bounds
    virtual bool hit(int x, int y);

    // handle a click
    virtual void click(int x, int y);

    // get the bounds
    virtual sf::FloatRect bounds();

    // get position
    virtual sf::Vector2f position();

    // sort children based on z order
    void sort();

    // dragged by debug gui
    virtual void onDragged(const Vector3 &diff);

    // my parent widget in the tree struct
    Widget *parent = nullptr;

    // my children in the tree struct
    WidgetList children;

    // height for render order
    int z_order = 0;

    // handle or ignore clicks
    bool clickable = false;

    // list of animations
    std::map<std::string, SpriteAnimation> animations;

    // is debugmode activated
    static bool debug;

    // widget is selected by debug tool
    bool grabbed = false;

    // every widget is associated with a game entity (controller)
    Entity *entity = nullptr;

protected:
    // draw the bounds rect
    virtual void draw_bounds(sf::RenderTarget &target);

    // current running animation
    SpriteAnimation *current_animation = nullptr;
};

} // namespace gamelib2
