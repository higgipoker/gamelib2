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
#include "../engine/engine.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include <SFML/Window/Event.hpp>
#include <iostream>

namespace gamelib2 {

// -----------------------------------------------------------------------------
// plain old function to find video modes
// -----------------------------------------------------------------------------
static bool valid_videomode(unsigned int width, unsigned int height) {
  // get list of supported video modes
  std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

  // search for one that matched the requested width and height
  for (auto &mode : modes) {
    std::cout << mode.width << "x" << mode.height << std::endl;
    if (mode.width == width && mode.height == height) {
      return true;
    }
  }

  return false;
}

// -----------------------------------------------------------------------------
// Viewer
// -----------------------------------------------------------------------------
Viewer::Viewer()
    : root_entity(std::make_unique<Entity>("root", "root")),
      root_widget(std::make_unique<Widget>()) {
  root_widget->connectEntity(root_entity.get());
  video_mode.width = 800;
  video_mode.height = 600;
  //    if (valid_videomode(video_mode.width, video_mode.height)) {
  //        window.create(video_mode, "test", sf::Style::Fullscreen);
  //    } else {
  //    std::cout << "no valid fullscreen videomode for " << video_mode.width
  //    << "x"
  //              << video_mode.height << std::endl;
  window.create(video_mode, "test", sf::Style::Default);
  // window.setPosition(sf::Vector2i(0, 0));

  //    sf::VideoMode vm = sf::VideoMode::getDesktopMode();
  //    window.create(vm, "test", sf::Style::Default);

  //    }

  view.reset(sf::FloatRect(0, 0, video_mode.width, video_mode.height));
  window.setView(view);
  ImGui::SFML::Init(window);
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
sf::RenderWindow &Viewer::getWindow() { return window; }

// -----------------------------------------------------------------------------
// startup
// -----------------------------------------------------------------------------
void Viewer::startup() {}

// -----------------------------------------------------------------------------
// close
// -----------------------------------------------------------------------------
void Viewer::close() {}

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
  // present
  // --------------------
  window.display();

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
  window.setView(engine->camera.view);
  root_widget->render(window);
  ImGui::SFML::Render(window);
}

// -----------------------------------------------------------------------------
// addWidget
// -----------------------------------------------------------------------------
void Viewer::addWidget(Widget *new_widget) {
  root_widget->addChild(new_widget);
}

// -----------------------------------------------------------------------------
// remWidget
// -----------------------------------------------------------------------------
void Viewer::remWidget(Widget *in_widget) {
  //
  auto w = root_widget.get();

  while (!w->children.empty()) {
    const auto original_size = w->children.size();
    // already found?
    w->children.erase(
        std::remove(w->children.begin(), w->children.end(), in_widget),
        w->children.end());

    if (w->children.size() != original_size) {
      for (auto &child : in_widget->children) {
        remWidget(child);
      }
      return;
    }
  }
}

// -----------------------------------------------------------------------------
// on_click
// -----------------------------------------------------------------------------
void Viewer::on_click(int x, int y, Widget &widget) {
  // process current widget
  if (widget.clickable) {
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
    ImGui::SFML::ProcessEvent(event);
    switch (event.type) {

    case sf::Event::Resized: {
    } break;

    case sf::Event::KeyReleased:
      if (event.key.code == sf::Keyboard::Tab) {
        Diagnostic::active(!Diagnostic::active());
      }
      break;

    case sf::Event::Closed:
      close();
      break;

    case sf::Event::KeyPressed:
      if (event.key.code == sf::Keyboard::Escape) {
        running = false;

      } else if (event.key.code == sf::Keyboard::P) {
        engine->paused = !engine->paused;
      }
      break;

    case sf::Event::MouseButtonPressed: {
      if (event.mouseButton.button == sf::Mouse::Left) {
        if (!mouse_pressed) {
          mouse_pressed = true;
          on_click(event.mouseButton.x + engine->camera.getViewInWorld().left,
                   event.mouseButton.y + engine->camera.getViewInWorld().top,
                   *root_widget);
          if (grabbed_widget) {
            if (grabbed_widget->clickable) {
              debug->selectEntity(grabbed_widget->entity);
              widget_grabbed = true;
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
  }
}

// -----------------------------------------------------------------------------
// connectEngine
// -----------------------------------------------------------------------------
void Viewer::connectEngine(Engine *in_engine) { engine = in_engine; }

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
  Widget *parent = root_widget.get();

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
}

// -----------------------------------------------------------------------------
// connectDiagnostics
// -----------------------------------------------------------------------------
void Viewer::connectDiagnostics(Diagnostic &d) {
  assert(debug == nullptr);
  debug = &d;
}
} // namespace gamelib2
