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

/**
 * @brief The EntityInterface class
 */
class EntityInterface {
 public:
  /**
   * @brief onDragged
   * @param diff
   */
  virtual void onDragged(const Vector3 &diff) = 0;
};

class Entity : public EntityInterface {
 public:
  /**
   * @brief Entity
   */
  Entity();
  virtual ~Entity() = default;

  /**
   * @brief create
   * @param in_type
   * @param in_name
   */
  void create(const std::string &in_type, const std::string &in_name);

  /**
   * @brief connectWidget
   * @param in_widget
   */
  void connectWidget(Widget *in_widget);

  /**
   * @brief update
   * @param dt
   */
  virtual void update(float dt);

  /**
   * @brief addAnimation
   * @param a_sprite_anim
   */
  virtual void addAnimation(const SpriteAnimation &a_sprite_anim);

  /**
   * @brief addAnimation
   * @param animname
   * @param frametime
   * @param loopanim
   * @param framelist
   */
  virtual void addAnimation(const std::string &animname, const float frametime,
                            bool loopanim, const std::vector<int> &framelist);

  /**
   * @brief startAnimation
   * @param a_name
   */
  virtual void startAnimation(const std::string &a_name);

  /**
   * @brief stopAnimation
   */
  virtual void stopAnimation();

  /**
   * @brief animate
   * @param in_dt
   */
  virtual void animate(float in_dt);

  /**
   * @brief currentAnimation
   * @return
   */
  SpriteAnimation *currentAnimation();

  /**
   * @brief getAnimationList
   * @return
   */
  const std::map<std::string, SpriteAnimation> &getAnimationList();

  /**
   * @brief onDragged
   * @param diff
   */
  void onDragged(const Vector3 &diff) override;

  // movement speed
  float speed = 100.0f;

  /**
   * @brief setPosition
   * @param x
   * @param y
   */
  void setPosition(float x, float y);

  /**
   * @brief setPosition
   * @param pos
   */
  void setPosition(const Vector3 &pos);

  // physical aspects
  Vector3 position;
  Vector3 velocity;
  Vector3 acceleration;
  Vector3 force;
  float mass = 1.0f;

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

  /**
   * @brief perspectivize
   * @param camera_height
   */
  virtual void perspectivize(float camera_height);
};

}  // namespace gamelib2
