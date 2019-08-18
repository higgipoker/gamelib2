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

#include "../camera/camera.hpp"
#include "../game/entity.hpp"
#include "../input/input.hpp"
#include "../types.hpp"
#include "../widgets/widget.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>

namespace gamelib2 {

class Diagnostic;

/**
 * @brief The Viewer class
 */
class Viewer {
 public:
  /**
   * @brief Viewer
   */
  Viewer();
  ~Viewer();

  /**
   * @brief configWindow
   * @param in_title
   * @param in_width
   * @param in_height
   * @param in_fullscreen
   * @param in_flags
   */
  void configWindow(const std::string &in_title, int in_width, int in_height,
                    Camera *in_cam, bool in_fullscreen = false,
                    int in_flags = sf::Style::Default);

  /**
   * @brief frame
   */
  void frame();

  /**
   * @brief close
   */
  void close();

  /**
   * @brief addWidget
   * @param new_widget
   * @param is_hud
   */
  void addWidget(Widget *new_widget, bool is_hud = false);

  /**
   * @brief remWidget
   * @param in_widget
   * @param is_hud
   */
  void remWidget(Widget *in_widget, bool is_hud = false);

  /**
   * @brief onMessage
   * @param in_message
   */
  void onMessage(const std::string &in_message);

  /**
   * @brief connectEngine
   * @param in_engine
   */
  void connectEngine(Engine &in_engine);

  /**
   * @brief connectDiagnostics
   * @param d
   */
  void connectDiagnostics(Diagnostic &d);

  /**
   * @brief getWindow
   * @return
   */
  sf::RenderWindow &getWindow();

  /**
   * @brief hasFocus
   * @return
   */
  bool hasFocus();
  bool running = true;
  float fps = 0;

 private:
  /**
   * @brief render
   */
  void render();

  /**
   * @brief get_input
   */
  void get_input();

  /**
   * @brief do_debug_ui
   */
  void do_debug_ui();

  /**
   * @brief on_click
   * @param x
   * @param y
   * @param widget
   */
  void on_click(float x, float y, Widget &widget);

  bool mouse_pressed = false;
  sf::RenderWindow window;
  sf::VideoMode video_mode;
  sf::View main_view;
  sf::View hud_view;
  Vector3 mouse;
  Widget root_widget;
  Widget root_hud;
  Camera *camera = nullptr;
  Widget *grabbed_widget = nullptr;
  bool widget_changed = false;
  bool widget_grabbed = false;
  sf::Clock fps_clock;
  sf::Time time;
  void calc_fps();

  Diagnostic *debug = nullptr;
  Engine *engine = nullptr;

  bool window_inited = false;
  int frames = 0;
};
}  // namespace gamelib2
