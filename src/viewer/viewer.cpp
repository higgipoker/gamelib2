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
#include <mutex>
#include <thread>

namespace gamelib2 {

static mygui gui;

// -----------------------------------------------------------------------------
// Viewer
// -----------------------------------------------------------------------------
Viewer::Viewer() {
}

// -----------------------------------------------------------------------------
// ~Viewer
// -----------------------------------------------------------------------------
Viewer::~Viewer() {
}

// -----------------------------------------------------------------------------
// startup
// -----------------------------------------------------------------------------
void Viewer::startup() {
    video_mode.width = 800;
    video_mode.height = 600;
    window.create(video_mode, "test", sf::Style::Titlebar);
    ImGui::SFML::Init(window);
    window.resetGLStates();
    window.setActive(false);

    gui.rect.width = 300;
    gui.rect.height = window.getSize().y;
    gui.rect.left = window.getSize().x - gui.rect.width + 6;
    gui.rect.top = 0;
}

// -----------------------------------------------------------------------------
// run
// -----------------------------------------------------------------------------
void Viewer::run(std::future<void> futureObj) {
    std::cout << "Viewer::run: start thread" << std::endl;

    // until exit signal received
    while (futureObj.wait_for(std::chrono::milliseconds(1)) ==
           std::future_status::timeout) {
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
    std::cout << "Viewer::run: end thread" << std::endl;
}

// -----------------------------------------------------------------------------
// render
// -----------------------------------------------------------------------------
void Viewer::render() {
    // std::lock_guard<std::mutex> lock(viewer_mutex);
    window.clear();
    root_widget->render(window);
    if (gui.visible) {
        do_debug_ui();
        ImGui::SFML::Render(window);
    }
}

// -----------------------------------------------------------------------------
// addWidget
// -----------------------------------------------------------------------------
void Viewer::addWidget(WidgetPtr &new_widget) {
    root_widget->addChild(new_widget);
}

// -----------------------------------------------------------------------------
// remWidget
// -----------------------------------------------------------------------------
void Viewer::remWidget(WidgetPtr &in_widget) {
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
            in_widget.reset();
            return;
        } else {
            for (auto &widget : w->children) {
                w = widget;
            }
        }
    }
}

// -----------------------------------------------------------------------------
// close
// -----------------------------------------------------------------------------
void Viewer::close() {
    running = false;
    ImGui::SFML::Shutdown();
    window.close();
}

// -----------------------------------------------------------------------------
// on_click
// -----------------------------------------------------------------------------
void Viewer::on_click(int x, int y, WidgetPtr &widget) {
    // std::lock_guard<std::mutex> lock(viewer_mutex);
    // process current widget
    if (widget->clickable) {
        if (widget->hit(x, y)) {
            widget->click(x, y);

            if (!gui.hover(x, y)) {
                if (widget.get() != grabbed_widget) {
                    widget_changed = true;
                    gui.scale = widget->scale();
                }
                grabbed_widget = widget.get();
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
                    close();
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
                    grabbed_widget->setPosition(abs_x, abs_y);
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
        for (auto &listener : keyboard_listeners) {
            listener->onEvent(event);
        }
        // the prev inputs were event triggered, now do realtime stuff
        pollAsyncInputs();
    }
}

// -----------------------------------------------------------------------------
// pollAsyncInputs
// -----------------------------------------------------------------------------
void Viewer::pollAsyncInputs() {
    // std::lock_guard<std::mutex> lock(viewer_mutex);

    if (keyboard.get() == nullptr)
        return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        keyboard->event_states[UP] = 1;
    } else {
        keyboard->event_states[UP] = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        keyboard->event_states[DOWN] = 1;
    } else {
        keyboard->event_states[DOWN] = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        keyboard->event_states[LEFT] = 1;
    } else {
        keyboard->event_states[LEFT] = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        keyboard->event_states[RIGHT] = 1;
    } else {
        keyboard->event_states[RIGHT] = 0;
    }
}

// -----------------------------------------------------------------------------
// do_debug_ui
// -----------------------------------------------------------------------------
void Viewer::do_debug_ui() {
    // std::lock_guard<std::mutex> lock(viewer_mutex);
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
// addKeyboardListener
// -----------------------------------------------------------------------------
void Viewer::addKeyboardListener(KeyboardListenerPtr &listener) {
    keyboard_listeners.emplace_back(listener);
}

// -----------------------------------------------------------------------------
// remKeyboardListener
// -----------------------------------------------------------------------------
void Viewer::remKeyboardListener(KeyboardListenerPtr &listener) {
    keyboard_listeners.erase(std::remove(keyboard_listeners.begin(),
                                         keyboard_listeners.end(), listener),
                             keyboard_listeners.end());

    listener.reset();
}

// -----------------------------------------------------------------------------
// connectKeyboard
// -----------------------------------------------------------------------------
void Viewer::connectKeyboard(std::shared_ptr<Keyboard> &in_keyboard) {
    keyboard = in_keyboard;
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
// calc_fps
// -----------------------------------------------------------------------------
void Viewer::calc_fps() {
    time = clock.getElapsedTime();
    fps = 1.0f / time.asSeconds();
    clock.restart().asSeconds();
}
} // namespace gamelib2
