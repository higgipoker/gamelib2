#include "sprite.hpp"

#include <assert.h>
#include <iostream>

#include "../math/vector.hpp"

namespace gamelib2 {

// -----------------------------------------------------------------------------
// Sprite
// -----------------------------------------------------------------------------
Sprite::Sprite() {
}

// -----------------------------------------------------------------------------
// Sprite
// -----------------------------------------------------------------------------
Sprite::Sprite(std::string a_filename, int a_rows, int a_cols) {
    init(a_filename, a_rows, a_cols);
}

// -----------------------------------------------------------------------------
// ~Sprite
// -----------------------------------------------------------------------------
Sprite::~Sprite() {
}

// -----------------------------------------------------------------------------
// init
// -----------------------------------------------------------------------------
void Sprite::init(std::string a_filename, int a_rows, int a_cols) {
    texture.Initialize(std::move(a_filename));
    sprite.setTexture(texture());

    // sprite sheet must have at least 1 row and col
    assert(a_rows && a_cols);

    // sanity check for texture
    assert(texture().getSize().x && texture().getSize().y);

    // set up the coordinates of each frame
    int sprite_width = static_cast<int>(texture().getSize().x) / a_cols;
    int sprite_height = static_cast<int>(texture().getSize().y) / a_rows;

    for (int row = 0; row < a_rows; row++) {
        for (int col = 0; col < a_cols; col++) {
            sf::IntRect rect(col * sprite_width, row * sprite_height,
                             sprite_width, sprite_height);
            rects.push_back(rect);
        }
    }
    sprite.setTextureRect(rects[0]);
}

// -----------------------------------------------------------------------------
// render
// -----------------------------------------------------------------------------
void Sprite::render(sf::RenderTarget &target) {
    target.draw(sprite);
    Widget::render(target);
}

// -----------------------------------------------------------------------------
// setFrame
// -----------------------------------------------------------------------------
void Sprite::setFrame(unsigned int a_frame) {
    // no bounds check, crash on out-of-range, should never happen
    sprite.setTextureRect(rects[a_frame]);
}

// -----------------------------------------------------------------------------
// addAnimation
// -----------------------------------------------------------------------------
void Sprite::addAnimation(SpriteAnimation a_sprite_anim) {
    animations.insert(
      std::make_pair(a_sprite_anim.name, std::move(a_sprite_anim)));
}

// ----------------------------------------------------------------------------------
// AddAnimation
// ----------------------------------------------------------------------------------
void Sprite::addAnimation(const std::string &animname, unsigned int frametime,
                          bool loopanim, std::vector<unsigned int> framelist) {
    addAnimation(SpriteAnimation(animname, frametime, loopanim, framelist));
}

// -----------------------------------------------------------------------------
// animate
// -----------------------------------------------------------------------------
void Sprite::animate() {
    if (current_animation) {
        setFrame(current_animation->step());
    }
}

// -----------------------------------------------------------------------------
// getBounds
// -----------------------------------------------------------------------------
sf::FloatRect Sprite::bounds() {
    return sprite.getGlobalBounds();
}

// -----------------------------------------------------------------------------
// move
// -----------------------------------------------------------------------------
void Sprite::move(int dx, int dy) {
    std::cout << "move by " << dx << ", " << dy << std::endl;
    sprite.move(dx, dy);
    Widget::move(dx, dy);
}

// -----------------------------------------------------------------------------
// position
// -----------------------------------------------------------------------------
sf::Vector2f Sprite::position() {
    return sprite.getPosition();
}

// -----------------------------------------------------------------------------
// scale
// -----------------------------------------------------------------------------
void Sprite::scale(float x, float y) {
    sprite.setScale(x, y);
}

// -----------------------------------------------------------------------------
// setPosition
// -----------------------------------------------------------------------------
void Sprite::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

// -----------------------------------------------------------------------------
// getScale
// -----------------------------------------------------------------------------
float Sprite::scale() {
    return sprite.getScale().x;
}

} // namespace gamelib2
