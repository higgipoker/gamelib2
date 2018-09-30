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
#include "../graphics/autotexture.hpp"
#include "../widgets/widget.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

namespace gamelib2 {

class TiledScrollingBackground : public Widget {
public:
    TiledScrollingBackground(const std::string &in_file);
    void init(const std::string &a_filename);
    void render(sf::RenderTarget &target) override;
    sf::FloatRect bounds() override;
    void setPosition(float x, float y) override;
    void move(float dx, float dy) override;
    sf::Vector2f position() override;

private:
    sf::FloatRect boundsrect;
    unsigned int total_width = 0, total_height = 0;
    unsigned int tile_width = 0, tile_height = 0;
    unsigned int tiles_wide = 0, tiles_high = 0;

    sf::Sprite sprite;
    AutoTexture texture;
};

} // namespace gamelib2
