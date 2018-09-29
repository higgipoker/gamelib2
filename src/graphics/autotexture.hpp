#ifndef AUTOTEXTURE_HPP
#define AUTOTEXTURE_HPP

#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <string>

namespace gamelib2 {

/**
 * @brief easier to read than a pair
 */
struct CountedTexture {
  CountedTexture(sf::Texture* a_texture, int a_count)
      : texture(a_texture), count(a_count) {}
  sf::Texture* texture = nullptr;
  int count = 0;
};

/**
 * @brief a reference counted wrapper for sf::texture so that sprites can share
 * textures without loading the same spriteset graphic loads of times
 *
 * texture is automatically deleted when no sprites are using it anymore
 */
class AutoTexture {
 public:
  /**
   * @brief AutoTexture
   */
  AutoTexture();

  /**
   * @brief AutoTexture
   * @param a_filename
   */
  AutoTexture(std::string a_filename);

  /**
   * @brief Initialize
   * @param a_filename
   */
  void Initialize(std::string a_filename);

  /**
   * destructor
   */
  ~AutoTexture();

  /**
   * @brief operator ()
   * @return
   */
  sf::Texture& operator()() { return *texture; }

 private:
  /// sf texture
  sf::Texture* texture = nullptr;

  /// track image filename
  std::string filename;

  /// static list of textures for ref counting
  static std::map<std::string, CountedTexture> textures;
};

}  // namespace gamelib2

#endif  // AUTOTEXTURE_HPP
