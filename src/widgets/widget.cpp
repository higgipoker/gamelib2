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
#include "widget.hpp"
#include "../game/entity.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
namespace gamelib2 {

bool Widget::debug = false;

// ------------------------------------------------------------------------------------------------------------
// sort predicate for widgets)
// ------------------------------------------------------------------------------------------------------------
struct {
    bool operator()(const Widget *w1, const Widget *w2) const {
        return w1->z_order < w2->z_order;
    }
} sort_widget;

// -----------------------------------------------------------------------------
// Widget
// -----------------------------------------------------------------------------
Widget::Widget() {
}

// -----------------------------------------------------------------------------
// ~Widget
// -----------------------------------------------------------------------------
Widget::~Widget() {
}

// -----------------------------------------------------------------------------
// getName
// -----------------------------------------------------------------------------
std::string Widget::getName() {
    if (entity) {
        return entity->name;
    }
    return "unknown widget";
}

// -----------------------------------------------------------------------------
// connectEntity
// -----------------------------------------------------------------------------
void Widget::connectEntity(Entity *in_entity) {
    entity = in_entity;
}

// -----------------------------------------------------------------------------
// releaseEntity
// -----------------------------------------------------------------------------
void Widget::releaseEntity() {
}

// -----------------------------------------------------------------------------
// render
// -----------------------------------------------------------------------------
void Widget::render(sf::RenderTarget &target) {
    for (auto &widget : children) {
        widget->render(target);
    }
    if (debug) {
        draw_bounds(target);
    }
}

// -----------------------------------------------------------------------------
// addChild
// -----------------------------------------------------------------------------
void Widget::addChild(Widget *in_widget) {
    children.emplace_back(in_widget);
}

// -----------------------------------------------------------------------------
// hit
// -----------------------------------------------------------------------------
bool Widget::hit(int x, int y) {
    return (bounds().contains(x, y));
}

// -----------------------------------------------------------------------------
// onClick
// -----------------------------------------------------------------------------
void Widget::click(int x, int y) {
}

// -----------------------------------------------------------------------------
// move
// -----------------------------------------------------------------------------
void Widget::move(float dx, float dy) {
    for (auto &child : children) {
        child->move(dx, dy);
    }
}

// -----------------------------------------------------------------------------
// setPosition
// -----------------------------------------------------------------------------
void Widget::setPosition(float x, float y) {
}

// -----------------------------------------------------------------------------
// position
// -----------------------------------------------------------------------------
sf::Vector2f Widget::position() {
    sf::Vector2f pos;
    return pos;
}

// -----------------------------------------------------------------------------
// addAnimation
// -----------------------------------------------------------------------------
void Widget::addAnimation(SpriteAnimation &a_sprite_anim) {
}

// -----------------------------------------------------------------------------
// addAnimation
// -----------------------------------------------------------------------------
void Widget::addAnimation(const std::string &animname, unsigned int frametime,
                          bool loopanim, std::vector<unsigned int> framelist) {
}

// -----------------------------------------------------------------------------
// startAnimation
// -----------------------------------------------------------------------------
void Widget::startAnimation(const std::string &a_name) {
    if (animations.find(a_name) != animations.end()) {
        current_animation = &(animations.find(a_name)->second);
        current_animation->start();
    }
}

// -----------------------------------------------------------------------------
// stopAnimation
// -----------------------------------------------------------------------------
void Widget::stopAnimation() {
    if (current_animation) {
        current_animation->stop();
        current_animation = nullptr;
    }
}

// -----------------------------------------------------------------------------
// stopAnimation
// -----------------------------------------------------------------------------
SpriteAnimation *Widget::currentAnimation() {
    return current_animation;
}

// -----------------------------------------------------------------------------
// draw_animate
// -----------------------------------------------------------------------------
void Widget::animate() {
}

// -----------------------------------------------------------------------------
// getScale
// -----------------------------------------------------------------------------
float Widget::scale() {
    return 1.f;
}

// -----------------------------------------------------------------------------
// getBounds
// -----------------------------------------------------------------------------
sf::FloatRect Widget::bounds() {
    return {};
}

// -----------------------------------------------------------------------------
// scale
// -----------------------------------------------------------------------------
void Widget::scale(float x, float y) {
}

// -----------------------------------------------------------------------------
// sort
// -----------------------------------------------------------------------------
void Widget::sort() {
    if (children.size() < 2)
        return;
    std::sort(children.begin(), children.end(), sort_widget);
}

// -----------------------------------------------------------------------------
// new_position
// -----------------------------------------------------------------------------
void Widget::onMoved(float x, float y, float dx, float dy) {
    if (entity) {
        entity->onMoved(Vector3(x, y), dx, dy);
    }
}

// -----------------------------------------------------------------------------
// draw_bounds
// -----------------------------------------------------------------------------
void Widget::draw_bounds(sf::RenderTarget &target) {
    std::vector<sf::Vertex> vertices;
    sf::FloatRect rect = bounds();

    // line 1
    vertices.emplace_back(
      sf::Vertex(sf::Vector2f(rect.left, rect.top),
                 grabbed ? sf::Color::White
                         : grabbed ? sf::Color::White : sf::Color::Magenta));

    vertices.emplace_back(
      sf::Vertex(sf::Vector2f(rect.left + rect.width, rect.top),
                 grabbed ? sf::Color::White : sf::Color::Magenta));

    // line 2
    vertices.emplace_back(
      sf::Vertex(sf::Vector2f(rect.left + rect.width, rect.top),
                 grabbed ? sf::Color::White : sf::Color::Magenta));

    vertices.emplace_back(
      sf::Vertex(sf::Vector2f(rect.left + rect.width, rect.top + rect.height),
                 grabbed ? sf::Color::White : sf::Color::Magenta));

    // line 3
    vertices.emplace_back(
      sf::Vertex(sf::Vector2f(rect.left + rect.width, rect.top + rect.height),
                 grabbed ? sf::Color::White : sf::Color::Magenta));

    vertices.emplace_back(
      sf::Vertex(sf::Vector2f(rect.left, rect.top + rect.height),
                 grabbed ? sf::Color::White : sf::Color::Magenta));

    // kline 4
    vertices.emplace_back(
      sf::Vertex(sf::Vector2f(rect.left, rect.top + rect.height),
                 grabbed ? sf::Color::White : sf::Color::Magenta));

    vertices.emplace_back(
      sf::Vertex(sf::Vector2f(rect.left, rect.top),
                 grabbed ? sf::Color::White : sf::Color::Magenta));

    target.draw(&vertices[0], vertices.size(), sf::Lines);

    grabbed = false;
}
} // namespace gamelib2
