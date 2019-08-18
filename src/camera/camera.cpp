#include "camera.hpp"

namespace gamelib2 {

// -----------------------------------------------------------------------------
// Init
// -----------------------------------------------------------------------------
void Camera::init(int width, int height) {
  view.setSize(static_cast<float>(width), static_cast<float>(height));
  view.setCenter(static_cast<float>(width / 2), static_cast<float>(height / 2));
}

// -----------------------------------------------------------------------------
// SetWorldrect
// -----------------------------------------------------------------------------
void Camera::setWorldRect(const sf::Rect<int> &world_rect) {
  world = world_rect;
}

// -----------------------------------------------------------------------------
// Follow
// -----------------------------------------------------------------------------
void Camera::follow(Entity *e) { target = e; }

static const float camera_speed = 2.0f;
// -----------------------------------------------------------------------------
// Update
// -----------------------------------------------------------------------------
void Camera::step(float dt) {
  if (target) {
    Vector3 distance =
        target->position - Vector3(view.getCenter().x, view.getCenter().y);
    float mag = distance.magnitude();
    velocity = distance.normalise() * camera_speed * dt * mag;
    position += velocity;
    update_position();
  }

  //	letterbox();
}

// -----------------------------------------------------------------------------
// update_position
// -----------------------------------------------------------------------------
void Camera::update_position() {
  // confine to world bounds
  sf::FloatRect v = getViewInWorld();

  // not too far left
  if (position.x - v.width / 2 < 0) {
    position.x = v.width / 2;
  }

  // not too far right
  if (position.x + v.width / 2 > world.width) {
    position.x = world.width - v.width / 2;
  }

  // not too far up
  if (position.y - v.height / 2 < 0) {
    position.y = v.height / 2;
  }

  // not too far down
  if (position.y + v.height / 2 > world.height) {
    position.y = world.height - v.height / 2;
  }

  view.setCenter(position.x, position.y);
}

// -----------------------------------------------------------------------------
// SetOffset
// -----------------------------------------------------------------------------
void Camera::letterbox() {
  float window_width = view.getSize().x;
  float window_height = view.getSize().y;

  float window_ratio = window_width / static_cast<float>(window_height);
  float view_ratio = view.getSize().x / static_cast<float>(view.getSize().y);
  float size_x = 1;
  float size_y = 1;
  float pos_x = 0;
  float pos_y = 0;

  bool horizontal_spacing = true;
  if (window_ratio < view_ratio) horizontal_spacing = false;

  // If horizontal_spacing is true, the black bars will appear on the left and
  // right side. Otherwise, the black bars will appear on the top and bottom.

  if (horizontal_spacing) {
    size_x = view_ratio / window_ratio;
    pos_x = (1 - size_x) / 2.f;
  }

  else {
    size_y = window_ratio / view_ratio;
    pos_y = (1 - size_y) / 2.f;
  }

  view.setViewport(sf::FloatRect(pos_x, pos_y, size_x, size_y));
}

// -----------------------------------------------------------------------------
// getViewInWorld
// -----------------------------------------------------------------------------
sf::FloatRect Camera::getViewInWorld() {
  float w = view.getSize().x * (view.getViewport().width);
  float h = view.getSize().y * (view.getViewport().height);
  float x = view.getCenter().x - w / 2;
  float y = view.getCenter().y - h / 2;

  sf::FloatRect rect(x, y, w, h);
  return rect;
}

void Camera::onWindowResized(int x, int y) {
  //  setSize(x, y);
  //  setCenter(x / 2, y / 2);
}

}  // namespace gamelib2
