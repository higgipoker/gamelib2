#pragma once
#include <iostream>
#include <map>
namespace gamelib2 {

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
class Compass {
 public:
  // construct default, with direction, or from vector
  Compass();
  Compass(Direction dir);
  Compass(const Vector3 &vec);

  // get a vector equivalent
  Vector3 toVector();

  // set from vector
  void fromVector(const Vector3 &v);

  // a compass direction
  Direction direction = Direction::NONE;

  // operator ==
  inline bool operator==(const Compass &rhs) {
    return direction == rhs.direction;
  }

  // operator !=
  inline bool operator!=(const Compass &rhs) {
    return direction != rhs.direction;
  }

  // output as string
  inline std::string print() {
   return direction_to_string[direction];
  }
};

}  // namespace gamelib2
