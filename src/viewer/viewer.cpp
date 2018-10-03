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
#include "../imgui/imgui-SFML.h"
#include "../imgui/imgui.h"
#include "mygui.hpp"
#include <SFML/Window/Event.hpp>
#include <iostream>

namespace gamelib2 {

static mygui gui;

// ------------------------------------------------------------------------------------------------------------
// plain old function to find video modes
// ------------------------------------------------------------------------------------------------------------
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
  : root_entity(new Entity("root"))
  , root_widget(new Widget()) {
    video_mode.width = 1024;
    video_mode.height = 768;
    //    if (valid_videomode(video_mode.width, video_mode.height)) {
    //        window.create(video_mode, "test", sf::Style::Fullscreen);
    //    } else {
    //    std::cout << "no valid fullscreen videomode for " << video_mode.width
    //    << "x"
    //              << video_mode.height << std::endl;
    window.create(video_mode, "test", sf::Style::Default);
    //    }
    ImGui::SFML::Init(window);
    window.resetGLStates();
    window.setActive(false);

    gui.rect.width = 300;
    gui.rect.height = window.getSize().y;
    gui.rect.left = window.getSize().x - gui.rect.width + 6;
    gui.rect.top = 0;

    view.reset(sf::FloatRect(0, 0, 800, 600));
    window.setView(view);
    sf::Joystick::update();
}

// -----------------------------------------------------------------------------
// ~Viewer
// -----------------------------------------------------------------------------
Viewer::~Viewer() {
    ImGui::SFML::Shutdown();
    running = false;
    window.close();
    delete root_entity;
    delete root_widget;
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
}

// -----------------------------------------------------------------------------
// run
// -----------------------------------------------------------------------------
void Viewer::run() {
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
    root_widget->render(window);
    if (gui.visible) {
        do_debug_ui();
        ImGui::SFML::Render(window);
    }
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
    auto w = root_widget;

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
void Viewer::on_click(int x, int y, Widget *widget) {

    // process current widget
    if (widget->clickable) {
        if (widget->hit(x, y)) {
            widget->click(x, y);

            if (!gui.hover(x, y)) {
                if (widget != grabbed_widget) {
                    widget_changed = true;
                    gui.scale = widget->scale();
                }
                grabbed_widget = widget;
                widget_grabbed = true;
            }
        }
    }

    // recursive call on children
    for (auto &child : widget->children) {
        on_click(x, y, child);
    }
}

// -----------------------------------------------------------------------------
// get_input
// -----------------------------------------------------------------------------
void Viewer::get_input() {

    static sf::Event event;
    while (window.pollEvent(event)) {
        if (gui.visible) {
            ImGui::SFML::ProcessEvent(event);
        }
        switch (event.type) {
        case sf::Event::KeyReleased:
            if (event.key.code == sf::Keyboard::Tab) {
                gui.visible = !gui.visible;
                Widget::debug = gui.visible;
            }
            break;

        case sf::Event::Closed:
            close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
                if (gui.visible) {
                    gui.visible = false;
                } else {
                    running = false;
                }
            } else if (event.key.code == sf::Keyboard::P) {
                engine->paused = !engine->paused;
            }
            break;

        case sf::Event::MouseButtonPressed: {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (gui.visible) {
                    // if (!gui.hover(event.mouseButton.x, event.mouseButton.y))
                    // {
                    on_click(event.mouseButton.x, event.mouseButton.y,
                             root_widget);
                    mouse_position.x = event.mouseButton.x;
                    mouse_position.y = event.mouseButton.y;
                    mouse_pressed = true;
                    // }
                }
            }
        } break;

        case sf::Event::MouseButtonReleased: {
            // grabbed_widget = nullptr;
            mouse_pressed = false;
            widget_grabbed = false;
        } break;

        case sf::Event::MouseMoved: {
            sf::Vector2i mouse_old = mouse_position;
            mouse_position.x = event.mouseMove.x;
            mouse_position.y = event.mouseMove.y;
            if (grabbed_widget) {
                sf::Vector2i delta = mouse_position - mouse_old;
                if (mouse_pressed && widget_grabbed) {
                    float abs_x = grabbed_widget->position().x + delta.x;
                    float abs_y = grabbed_widget->position().y + delta.y;
                    grabbed_widget->onMoved(abs_x, abs_y, delta.x, delta.y);
                }
            }
        } break;

        case sf::Event::MouseWheelScrolled:
            if (gui.visible && gui.hover(mouse_position.x, mouse_position.y)) {
                if (event.mouseWheelScroll.delta > 0) {
                    gui.alpha += 0.1;
                } else {
                    gui.alpha -= 0.1;
                }
                if (gui.alpha < 0) {
                    gui.alpha = 0;
                } else if (gui.alpha > 1) {
                    gui.alpha = 1;
                }
            }
            break;
        }
    }
}

// -----------------------------------------------------------------------------
// do_debug_ui
// -----------------------------------------------------------------------------
void Viewer::do_debug_ui() {

    Widget::debug = true;
    ImGui::SFML::Update(window, gui.deltaClock.restart());
    ImGui::SetNextWindowSize(sf::Vector2f(gui.rect.width, gui.rect.height));
    ImGui::SetNextWindowPos(sf::Vector2f(gui.rect.left, gui.rect.top));
    ImGui::SetNextWindowBgAlpha(gui.alpha);
    ImGui::Begin(gui.window_title.c_str(), nullptr, gui.flags);
    ImGui::Text("%d fps", static_cast<int>(fps));

    if (grabbed_widget) {
        gui.showSpriteFrame(*grabbed_widget);
        grabbed_widget->grabbed = true;
    }

    ImGui::End();
}

// -----------------------------------------------------------------------------
// connectEngine
// -----------------------------------------------------------------------------
void Viewer::connectEngine(Engine *in_engine) {
    assert(in_engine != nullptr);
    engine = in_engine;
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
    Widget *parent = root_widget;

    while (!parent->children.empty()) {
        parent->sort();
        parent = parent->children[0];
    }
}

// -----------------------------------------------------------------------------
// calc_fps
// -----------------------------------------------------------------------------
void Viewer::calc_fps() {
    time = clock.getElapsedTime();
    fps = 1.0f / time.asSeconds();
    clock.restart().asSeconds();
}
} // namespace gamelib2
