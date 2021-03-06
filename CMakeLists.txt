cmake_minimum_required (VERSION 2.6)

# This line will export your dependency's symbols and make them available to your project on Windows. Without this your code will compile but it won't run on Windows!
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# ------------------------------------------------------------------------------
# use c++11
if (WIN32)
    add_definitions(-std:c++latest)
endif (WIN32)

if (UNIX)
    add_definitions(-std=c++17)
endif (UNIX)

# ------------------------------------------------------------------------------
# project name
project (gamelib2)



# ------------------------------------------------------------------------------
# library output folder
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib/$<0:>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib/$<0:>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib/$<0:>)

# ------------------------------------------------------------------------------
# export for windows
set(CMAKE_EXPORT_COMPILE_COMMANDS ON )

# ------------------------------------------------------------------------------
# include dirs
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# --------------------------------------------------
# lib dirs
# --------------------------------------------------
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../SFML-2.5.1/lib) # self built sfml

# ------------------------------------------------------------------------------
# project build
add_library(gamelib2 SHARED
src/debug/diagnostic.cpp
src/debug/joystick.cpp
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
src/imgui/imgui.cpp
src/imgui/imgui_draw.cpp
src/imgui/imgui_widgets.cpp
src/imgui/imgui_demo.cpp
src/imgui/imgui-SFML.cpp
)

# ------------------------------------------------------------------------------
# dll export for windows
if(MSVC)
    target_compile_definitions(gamelib2 PRIVATE WIN_EXPORT)
endif()

# ------------------------------------------------------------------------------
# install headers
INSTALL ( DIRECTORY src/
  DESTINATION ${CMAKE_BINARY_DIR}/../../include/gamelib2
  FILES_MATCHING PATTERN "*.h*"
  )

# ------------------------------------------------------------------------------
# link SFML DEBUG
target_link_libraries (gamelib2 debug sfml-graphics-d)
target_link_libraries (gamelib2 debug sfml-window-d)
target_link_libraries (gamelib2 debug sfml-system-d)

# ------------------------------------------------------------------------------
# link SFML RELEASE
target_link_libraries (gamelib2 optimized sfml-graphics)
target_link_libraries (gamelib2 optimized sfml-window)
target_link_libraries (gamelib2 optimized sfml-system)

find_package(OpenGL)
target_link_libraries (gamelib2 ${OPENGL_gl_LIBRARY})
