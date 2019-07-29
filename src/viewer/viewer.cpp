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
#include "viewer.hpp"
#include "../debug/diagnostic.hpp"
#include "../engine/engine.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include <SFML/Window/Event.hpp>
#include <iostream>

namespace gamelib2 {

// -----------------------------------------------------------------------------
// plain old function to find video modes
// -----------------------------------------------------------------------------
static bool valid_videomode(int width, int height) {
  // get list of supported video modes
  std::vector< sf::VideoMode > modes = sf::VideoMode::getFullscreenModes();

  // search for one that matched the requested width and height
  for (auto &mode : modes) {
    std::cout << mode.width << "x" << mode.height << std::endl;
    if (mode.width == width && mode.height == height) {
      return true;
    }
  }

  std::cout << "no valid fullscreen videomode for " << width << "x" << height << std::endl;
  return false;
}

// -----------------------------------------------------------------------------
// Viewer
// -----------------------------------------------------------------------------
Viewer::Viewer() {
}

void Viewer::configWindow(const std::string &in_title, int in_width, int in_height,
                          bool in_fullscreen, int in_flags) {
  assert(window_inited == false);
  video_mode.width = in_width;
  video_mode.height = in_height;
  if (in_fullscreen && valid_videomode(video_mode.width, video_mode.height)) {
    window.create(video_mode, in_title, sf::Style::Fullscreen);
  } else {
    sf::VideoMode vm = sf::VideoMode::getDesktopMode();
    vm.width = in_width;
    vm.height = in_height;
    window.create(vm, in_title, in_flags);
  }
  //window.setVerticalSyncEnabled(false);
  //window.setFramerateLimit(60);
  window_inited = true;
}

// -----------------------------------------------------------------------------
// ~Viewer
// -----------------------------------------------------------------------------
Viewer::~Viewer() {
  running = false;
  window.close();
}

// -----------------------------------------------------------------------------
// getWindow
// -----------------------------------------------------------------------------
sf::RenderWindow &Viewer::getWindow() {
  return window;
}

// -----------------------------------------------------------------------------
// startup
// -----------------------------------------------------------------------------
void Viewer::startup() {
}

// -----------------------------------------------------------------------------
// close
// -----------------------------------------------------------------------------
void Viewer::close() {
  window.close();
}

// -----------------------------------------------------------------------------
// run
// -----------------------------------------------------------------------------
void Viewer::frame() {
  // --------------------
  // input
  // --------------------
  get_input();

  // --------------------
  // render
  // --------------------
  render();

  // --------------------
  // fps
  // --------------------
  calc_fps();
}

// -----------------------------------------------------------------------------
// render
// -----------------------------------------------------------------------------
void Viewer::render() {
  window.clear();
  sort_widgets();

  root_widget.render(window);

  window.setView(hud_view);
  root_hud.render(window);

  if (debug->active()) {
    debug->render();
  }

  window.display();
}

// -----------------------------------------------------------------------------
// addWidget
// -----------------------------------------------------------------------------
void Viewer::addWidget(Widget *new_widget, bool is_hud) {
  if(is_hud){
    root_hud.addChild(new_widget);
  }else{
    root_widget.addChild(new_widget);
  }
}

// -----------------------------------------------------------------------------
// remWidget
// -----------------------------------------------------------------------------
void Viewer::remWidget(Widget *in_widget, bool is_hud) {
   if (in_widget->parent) {
    in_widget->parent->children.erase(std::remove(in_widget->parent->children.begin(),
                                                  in_widget->parent->children.end(), in_widget),
                                      in_widget->parent->children.end());
  }
}

// -----------------------------------------------------------------------------
// on_click
// -----------------------------------------------------------------------------
void Viewer::on_click(float x, float y, Widget &widget) {
  // process current widget
  if (widget.clickable) {
    // widget.anchor(); // tmp - anchor changes on screen position for some
    // widgets
    if (widget.hit(x, y)) {
      widget.click(x, y);
      grabbed_widget = &widget;
    }
  }

  // recursive call on children
  for (auto &child : widget.children) {
    on_click(x, y, *child);
  }
}

// -----------------------------------------------------------------------------
// get_input
// -----------------------------------------------------------------------------
void Viewer::get_input() {
  static sf::Event event;
  while (window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Resized: {
      } break;

      case sf::Event::KeyReleased:
        if (event.key.code == sf::Keyboard::Tab) {
          if (hasFocus()) {
#ifndef NDEBUG
            Diagnostic::active(!Diagnostic::active());

            if (!Diagnostic::active()) {
              if (debug) {
                debug->onClose();
              }
            }
#endif
          }
        }
        break;

      case sf::Event::Closed:
        running = false;
        break;

      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape) {
          if (hasFocus()) {
            if (Diagnostic::active()) {
              Diagnostic::active(!Diagnostic::active());
              if (debug) {
                debug->onClose();
              }
            } else {
              running = false;
            }
          }

        } else if (event.key.code == sf::Keyboard::P) {
          if (engine) {
            engine->paused = !engine->paused;
          }
        }
        break;

      case sf::Event::MouseButtonPressed: {
        if (event.mouseButton.button == sf::Mouse::Left) {
          if (Diagnostic::active()) {
            if (!mouse_pressed) {
              // get the current mouse position in the window
              sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
              // convert it to world coordinates
              sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
              mouse_pressed = true;
              on_click(worldPos.x, worldPos.y, root_widget);
              if (grabbed_widget) {
                if (grabbed_widget->clickable) {
                  debug->selectEntity(grabbed_widget->entity);
                  widget_grabbed = true;
                }
              }
            }
          }
        }
      } break;

      case sf::Event::MouseButtonReleased: {
        grabbed_widget = nullptr;
        mouse_pressed = false;
        widget_grabbed = false;
      } break;

      case sf::Event::MouseMoved: {
        // get the current mouse position in the window
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        // convert it to world coordinates
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
        Vector3 mouse_old = mouse;
        mouse.x = worldPos.x;
        mouse.y = worldPos.y;
        Vector3 mouse_delta = mouse - mouse_old;
        if (grabbed_widget && grabbed_widget->entity) {
          if (mouse_pressed && widget_grabbed) {
            grabbed_widget->onDragged(mouse_delta);
          }
        }
      } break;

      case sf::Event::MouseWheelScrolled:
        break;
    }

    if (debug->active()) {
      ImGui::SFML::ProcessEvent(event);
    }
  }
}

// -----------------------------------------------------------------------------
// onMessage
// -----------------------------------------------------------------------------
void Viewer::onMessage(const std::string &in_message) {
  std::cout << "message received: " << in_message << std::endl;
}

// -----------------------------------------------------------------------------
// sort_widgets
// -----------------------------------------------------------------------------
void Viewer::sort_widgets() {
  Widget *parent = &root_widget;

  while (!parent->children.empty()) {
    parent->sort();
    parent = parent->children[0];
  }
}

// -----------------------------------------------------------------------------
// calc_fps
// -----------------------------------------------------------------------------
void Viewer::calc_fps() {
  time = fps_clock.getElapsedTime();
  fps = 1.0f / time.asSeconds();
  fps_clock.restart().asSeconds();

  if (debug) {
    debug->fps_history.push_back(fps);
    if (debug->fps_history.size() > 1000) {
      debug->fps_history.pop_front();
    }
  }
}

// -----------------------------------------------------------------------------
// connectEngine
// -----------------------------------------------------------------------------
void Viewer::connectEngine(Engine &e) {
  assert(engine == nullptr);
  engine = &e;
}

// -----------------------------------------------------------------------------
// connectDiagnostics
// -----------------------------------------------------------------------------
void Viewer::connectDiagnostics(Diagnostic &d) {
  assert(debug == nullptr);
  debug = &d;
}

// -----------------------------------------------------------------------------
// setView
// -----------------------------------------------------------------------------
void Viewer::setView(sf::View view) {
  window.setView(view);

  hud_view.reset(sf::FloatRect(0,0,view.getSize().x, view.getSize().y));
}

// -----------------------------------------------------------------------------
// hasFocus
// -----------------------------------------------------------------------------
bool Viewer::hasFocus() {
  return window.hasFocus();
}
} // namespace gamelib2
