#include "autotexture.hpp"
#include <iostream>

namespace gamelib2 {
std::map<std::string, CountedTexture> AutoTexture::textures;

// -----------------------------------------------------------------------------
// AutoTexture
// -----------------------------------------------------------------------------
AutoTexture::AutoTexture() = default;

// -----------------------------------------------------------------------------
// AutoTexture
// -----------------------------------------------------------------------------
AutoTexture::AutoTexture(std::string a_filename) {
    Initialize(std::move(a_filename));
}

// -----------------------------------------------------------------------------
// ~Initialize
// -----------------------------------------------------------------------------
void AutoTexture::Initialize(std::string a_filename) {
    filename = std::move(a_filename);
    // only create new texture if doesnt exist already
    auto tex = textures.find(filename);
    if (tex != textures.end()) {
        texture = (*tex).second.texture;
        ++(*tex).second.count;
    } else {
        std::cout << "new texture: " << filename << std::endl;
        texture = new sf::Texture();
        texture->loadFromFile(filename);
        textures.insert(std::make_pair(filename, CountedTexture(texture, 1)));
    }
}

// -----------------------------------------------------------------------------
// ~AutoTexture
// -----------------------------------------------------------------------------
AutoTexture::~AutoTexture() {
    auto tex = textures.find(filename);
    if (tex != textures.end()) {
        if (--(*tex).second.count == 0) {
            std::cout << "delete texture: " << filename << std::endl;
            textures.erase(filename);

            // this was the last AutoTexture pointing to this mem, so delete now
            delete texture;
        }
    }
}
} // namespace gamelib2
