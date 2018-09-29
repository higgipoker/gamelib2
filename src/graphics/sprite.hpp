#ifndef GAMELIB2_SPRITE_HPP__
#define GAMELIB2_SPRITE_HPP__

#include "../widgets/widget.hpp"
#include "autotexture.hpp"
#include "renderable.hpp"
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
    Sprite(std::string a_filename, int a_rows, int a_cols);
    ~Sprite() override;

    void render(sf::RenderTarget &target) override;
    void init(std::string a_filename, int a_rows, int a_cols);
    void setFrame(unsigned int a_frame);
    void addAnimation(SpriteAnimation a_sprite_anim) override;
    void addAnimation(const std::string &animname, unsigned int frametime,
                      bool loopanim,
                      std::vector<unsigned int> framelist) override;
    void animate() override;
    void move(int dx, int dy) override;
    void setPosition(float x, float y) override;
    void scale(float x, float y) override;
    float scale() override;
    sf::FloatRect bounds() override;
    sf::Vector2f position() override;

  private:
    AutoTexture texture;
    std::vector<sf::IntRect> rects;
    sf::Sprite sprite;
};

} // namespace gamelib2

#endif // SPRITE_HPP
