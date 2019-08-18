#pragma once
#include <iostream>
#include <map>
namespace gamelib2 {

/**
 * @brief The Direction enum
 */
enum class Direction {
  NORTH,
  NORTH_EAST,
  EAST,
  SOUTH_EAST,
  SOUTH,
  SOUTH_WEST,
  WEST,
  NORTH_WEST,
  NONE
};

static std::map<Direction, std::string> direction_to_string = {
    std::make_pair(Direction::NORTH, "NORTH"),
    std::make_pair(Direction::NORTH_EAST, "NORTH_EAST"),
    std::make_pair(Direction::EAST, "EAST"),
    std::make_pair(Direction::SOUTH_EAST, "SOUTH_EAST"),
    std::make_pair(Direction::SOUTH, "SOUTH"),
    std::make_pair(Direction::SOUTH_WEST, "SOUTH_WEST"),
    std::make_pair(Direction::WEST, "WEST"),
    std::make_pair(Direction::NORTH_WEST, "NORTH_WEST"),
    std::make_pair(Direction::NONE, "NONE"),
};

class Vector3;

/**
 * @brief The Compass class
 */
class Compass {
 public:
  /**
   * @brief Compass
   */
  Compass();

  /**
   * @brief Compass
   * @param dir
   */
  Compass(Direction dir);

  /**
   * @brief Compass
   * @param vec
   */
  Compass(const Vector3 &vec);

  /**
   * @brief toVector
   * @return
   */
  Vector3 toVector();

  /**
   * @brief fromVector
   * @param v
   */
  void fromVector(const Vector3 &v);

  /**
   * @brief direction
   */
  Direction direction = Direction::NONE;

  /**
   * @brief operator ==
   * @param rhs
   * @return
   */
  inline bool operator==(const Compass &rhs) {
    return direction == rhs.direction;
  }

  /**
   * @brief operator !=
   * @param rhs
   * @return
   */
  inline bool operator!=(const Compass &rhs) {
    return direction != rhs.direction;
  }

  /**
   * @brief print
   * @return
   */
  inline std::string print() { return direction_to_string[direction]; }
};

}  // namespace gamelib2
