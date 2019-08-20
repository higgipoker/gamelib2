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
// Initialize
// -----------------------------------------------------------------------------
void AutoTexture::Initialize(std::string a_filename) {
  filename = std::move(a_filename);
  // only create new texture if doesnt exist already
  auto tex = textures.find(filename);
  if (tex != textures.end()) {
    texture = (*tex).second.texture;
    ++(*tex).second.count;
  } else {
    texture = std::make_shared<sf::Texture>();
    texture->loadFromFile(filename);
    textures.insert(std::make_pair(filename, CountedTexture(texture, 1)));
    std::cout << "load texture from " << filename << std::endl;
  }
}
}  // namespace gamelib2
