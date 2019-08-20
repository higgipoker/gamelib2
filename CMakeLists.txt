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

# --------------------------------------------------
# compiler specific
# --------------------------------------------------
if(MSVC)
    # Set the DLLEXPORT variable to export symbols
    target_compile_definitions(gamelib2 PRIVATE WIN_EXPORT)
endif()

set(HEADERS
    src/debug/diagnostic.hpp
    src/debug/joystick.hpp
    src/statemachine/state_machine.hpp
    src/statemachine/state.hpp
    src/engine/engine.hpp
    src/engine/framerate.hpp
    src/math/vector.hpp
    src/viewer/viewer.hpp
    src/widgets/widget.hpp
    src/game/game.hpp
    src/game/entity.hpp
    src/graphics/autotexture.hpp
    src/graphics/primitives.hpp
    src/widgets/spriteanimation.hpp
    src/widgets/sprite.hpp
    src/widgets/label.hpp
    src/widgets/tiledscrollingbackground.hpp
    src/math/vector.hpp
    src/utils/file.hpp
    src/utils/files.hpp
    src/utils/tree.hpp
    src/utils/timer.hpp
    src/utils/grid.hpp
    src/input/device.hpp
    src/input/keyboard.hpp
    src/input/xbox_gamepad.hpp
    src/compass/compass.hpp
    src/physics/collisions.hpp
    src/camera/camera.hpp
    src/types.hpp
    src/imgui/imgui.hpp
    src/imgui/imgui_draw.hpp
    src/imgui/imgui_widgets.hpp
    src/imgui/imgui_demo.hpp
    src/imgui/imgui-SFML.hpp
    )
INSTALL ( DIRECTORY src/
  DESTINATION ${CMAKE_BINARY_DIR}/../../include/gamelib2
  FILES_MATCHING PATTERN "*.hpp"
  )

find_package(OpenGL)
target_link_libraries (gamelib2 sfml-graphics-d)
target_link_libraries (gamelib2 sfml-window-d)
target_link_libraries (gamelib2 sfml-system-d)
target_link_libraries (gamelib2 ${OPENGL_gl_LIBRARY})
