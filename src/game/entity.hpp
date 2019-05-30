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
#include <map>
#include <string>
#include "../input/input.hpp"
#include "../input/keyboard.hpp"
#include "../math/vector.hpp"
#include "../types.hpp"
#include "../widgets/spriteanimation.hpp"

namespace gamelib2 {

class Widget;

// a debug interface that all entities must implement
class EntityInterface {
 public:
  // the entity was manually moved
  virtual void onDragged(const Vector3 &diff) = 0;
};

class Entity : public EntityInterface {
 public:
  // construct / destruct
  Entity();
  virtual ~Entity() = default;

  // create with a name id
  void create(const std::string &in_type, const std::string &in_name);

  // a game entity is associated with a widget
  void connectWidget(Widget *in_widget);

  // main update
  virtual void update(float dt);

  // add an animation by pointer
  virtual void addAnimation(const SpriteAnimation &a_sprite_anim);

  // add an animation by params
  virtual void addAnimation(const std::string &animname, const float frametime,
                            bool loopanim, const std::vector<int> &framelist);

  // start an animation
  virtual void startAnimation(const std::string &a_name);

  // stop an animation
  virtual void stopAnimation();

  // update the animation
  virtual void animate(float in_dt);

  // get currently active animation
  SpriteAnimation *currentAnimation();

  // get animation list
  const std::map<std::string, SpriteAnimation> &getAnimationList();

  // debug interface
  void onDragged(const Vector3 &diff) override;

  // movement speed
  float speed = 100.0f;

  // helper to set position through a function
  void setPosition(float x, float y);
  void setPosition(const Vector3 &pos);

  // physical aspects
  Vector3 position;
  Vector3 velocity;
  Vector3 acceleration;

  // type id
  std::string type;

  // identifier name
  std::string name;

  // entity is associated with a widget
  Widget *widget = nullptr;

 protected:
  // entity can animate its widget
  std::map<std::string, SpriteAnimation> animations;

  // current running animation
  SpriteAnimation *current_animation = nullptr;

  // optionally add perspective
  virtual void perspectivize(float camera_height);
};

}  // namespace gamelib2
