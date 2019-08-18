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
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <map>
#include <string>
#include "../math/vector.hpp"
#include "../types.hpp"

namespace gamelib2 {

/**
 * @brief The AnchorType enum
 */
enum AnchorType { ANCHOR_TOP_LEFT, ANCHOR_CENTER, ANCHOR_BASE_CENTER };

class Entity;

/**
 * @brief The Widget class
 */
class Widget {
 public:
  /**
   * @brief Widget
   */
  Widget(const std::string &_name);

  /**
   * @brief ~Widget
   */
  virtual ~Widget();

  /**
   * @brief connectEntity
   * @param in_entity
   */
  virtual void connectEntity(Entity *in_entity);

  /**
   * @brief releaseEntity
   */
  virtual void releaseEntity();

  /**
   * @brief getName
   * @return
   */
  std::string getName();

  /**
   * @brief render
   * @param target
   */
  virtual void render(sf::RenderTarget &target);

  /**
   * @brief addChild
   * @param in_widget
   */
  virtual void addChild(Widget *in_widget);

  /**
   * @brief move
   * @param dx
   * @param dy
   */
  virtual void move(float dx, float dy);

  /**
   * @brief setPosition
   * @param x
   * @param y
   */
  virtual void setPosition(float x, float y);

  /**
   * @brief scale
   * @param x
   * @param y
   */
  virtual void scale(float x, float y);

  /**
   * @brief scale
   * @return
   */
  virtual sf::Vector2f scale();

  /**
   * @brief hit
   * @param x
   * @param y
   * @return
   */
  virtual bool hit(float x, float y);

  /**
   * @brief click
   * @param x
   * @param y
   */
  virtual void click(float x, float y);

  /**
   * @brief bounds
   * @return
   */
  virtual sf::FloatRect bounds();

  /**
   * @brief position
   * @return
   */
  virtual sf::Vector2f position();

  /**
   * @brief sort
   */
  void sort();

  /**
   * @brief onDragged
   * @param diff
   */
  virtual void onDragged(const Vector3 &diff);

  /**
   * @brief anchor
   */
  void anchor();

  // my parent widget in the tree struct
  Widget *parent = nullptr;

  // my children in the tree struct
  std::vector<Widget *> children;

  // height for render order
  int z_order = 0;

  // handle or ignore clicks
  bool clickable = false;

  // is debugmode activated
  static bool debug;

  // widget is selected by debug tool
  bool grabbed = false;

  // every widget is associated with a game entity (controller)
  Entity *entity = nullptr;

  // how the widget is displayed inrelation to x,y position
  AnchorType anchor_type = ANCHOR_CENTER;

  // a list of drawable primitives for debug
  std::vector<sf::VertexArray> primitives;

  // a list of drawable shapes for debug
  std::vector<sf::Shape *> shapes;

  // fordebug
  std::string name;

 protected:
  /**
   * @brief draw_bounds
   * @param target
   */
  virtual void draw_bounds(sf::RenderTarget &target);
};

}  // namespace gamelib2
