cmake_minimum_required (VERSION 2.6)

# ------------------------------------------------------------------------------
# use c++11
add_definitions(-std=c++11)

# ------------------------------------------------------------------------------
# project name
project (gamelib2)

# ------------------------------------------------------------------------------
# library output folder
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# ------------------------------------------------------------------------------
# include dirs
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../SFML-2.5.0/include)

# ------------------------------------------------------------------------------
# project build
add_library(gamelib2 SHARED
src/statemachine/state_machine.cpp
src/statemachine/state.cpp
src/engine/engine.cpp
src/math/vector.cpp
src/imgui/imgui_widgets.cpp
src/imgui/imgui-SFML.cpp
src/imgui/imgui_draw.cpp
src/imgui/imgui.cpp
src/viewer/mygui.cpp
src/viewer/viewer.cpp
src/widgets/widget.cpp
src/game/entity.cpp
src/graphics/autotexture.cpp
src/widgets/spriteanimation.cpp
src/widgets/sprite.cpp
src/widgets/tiledscrollingbackground.cpp
src/math/vector.cpp
src/utils/files.cpp
src/utils/tree.cpp
src/utils/timer.cpp
src/input/keyboard.cpp
src/input/controller.cpp
src/compass/compass.cpp
src/physics/collisions.cpp
)
