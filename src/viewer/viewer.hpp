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

#include "../game/entity.hpp"
#include "../input/input.hpp"
#include "../types.hpp"
#include "../widgets/widget.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>

namespace gamelib2 {

class Diagnostic;

class Viewer {
 public:
   Viewer();
  ~Viewer();
  void configWindow(const std::string &in_title, int in_width, int in_height, bool in_fullscreen = false, int in_flags = sf::Style::Default);
  void startup();
  void frame();
  void close();
  void addWidget(Widget *new_widget);
  void remWidget(Widget *in_widget);
  void onMessage(const std::string &in_message);
  void connectEngine(Engine &in_engine);
  void connectDiagnostics(Diagnostic &d);
  sf::RenderWindow &getWindow();
  void setView(sf::View view);
  bool hasFocus();
  bool running = true;
  float fps = 0;

 private:
  void render();
  void get_input();
  void do_debug_ui();
  void on_click(float x, float y, Widget &widget);
  void sort_widgets();
  bool mouse_pressed = false;
  sf::RenderWindow window;
  sf::VideoMode video_mode;
  Vector3 mouse;
  Widget root_widget;
  Widget *grabbed_widget = nullptr;
  bool widget_changed = false;
  bool widget_grabbed = false;
  sf::Clock fps_clock;
  sf::Time time;
  void calc_fps();

  Diagnostic *debug = nullptr;
  Engine *engine = nullptr;

  bool window_inited = false;
};
}  // namespace gamelib2
