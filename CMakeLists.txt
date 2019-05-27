cmake_minimum_required (VERSION 2.6)

# ------------------------------------------------------------------------------
# use c++11
add_definitions(-std=c++17)

# ------------------------------------------------------------------------------
# project name
project (gamelib2)

# ------------------------------------------------------------------------------
# library output folder
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# ------------------------------------------------------------------------------
# include dirs
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../SFML-2.5.0/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../imgui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../imgui-sfml)

# ------------------------------------------------------------------------------
# project build
add_library(gamelib2 SHARED
src/debug/diagnostic.cpp
src/statemachine/state_machine.cpp
src/statemachine/state.cpp
src/engine/engine.cpp
src/engine/framerate.cpp
src/math/vector.cpp
src/viewer/viewer.cpp
src/widgets/widget.cpp
src/game/game.cpp
src/game/entity.cpp
src/graphics/autotexture.cpp
src/graphics/primitives.cpp
src/widgets/spriteanimation.cpp
src/widgets/sprite.cpp
src/widgets/label.cpp
src/widgets/tiledscrollingbackground.cpp
src/math/vector.cpp
src/utils/file.cpp
src/utils/files.cpp
src/utils/tree.cpp
src/utils/timer.cpp
src/utils/grid.cpp
src/input/device.cpp
src/input/keyboard.cpp
src/input/xbox_gamepad.cpp
src/compass/compass.cpp
src/physics/collisions.cpp
src/camera/camera.cpp
src/types.hpp
)
