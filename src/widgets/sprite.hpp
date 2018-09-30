#pragma once

#include "../graphics/autotexture.hpp"
#include "../widgets/widget.hpp"
#include "spriteanimation.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <set>

namespace gamelib2 {

/**
 * @brief The Sprite class
 */
class Sprite : public Widget {
public:
    Sprite();
    Sprite(const std::string &a_filename, int a_rows, int a_cols);
    ~Sprite() override;

    void render(sf::RenderTarget &target) override;
    void init(std::string a_filename, int a_rows, int a_cols);
    void animate() override;
    void move(float dx, float dy) override;
    void setPosition(float x, float y) override;
    void scale(float x, float y) override;
    float scale() override;
    void connectShadow(WidgetPtrWeak &spr);
    void setFrame(unsigned int a_frame);
    unsigned int getFrame();
    void addAnimation(SpriteAnimation &a_sprite_anim) override;
    void addAnimation(const std::string &animname, unsigned int frametime,
                      bool loopanim,
                      std::vector<unsigned int> framelist) override;
    sf::FloatRect bounds() override;
    sf::Vector2f position() override;

    float image_width;
    float image_height;
    bool has_shadow = false;
    WidgetPtrWeak shadow;

private:
    AutoTexture texture;
    std::vector<sf::IntRect> rects;
    sf::Sprite sprite;
};

} // namespace gamelib2
