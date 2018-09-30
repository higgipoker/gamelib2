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
#include "../input/keyboardlistener.hpp"
#include "../types.hpp"
#include "../widgets/widget.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <future>
#include <map>

namespace gamelib2 {

class Engine;
class Viewer {
public:
    Viewer();
    ~Viewer();
    void startup();
    void run(std::future<void> futureObj);
    void close();
    void addWidget(WidgetPtr &new_widget);
    void remWidget(WidgetPtr &in_widget);
    void addKeyboardListener(KeyboardListenerPtr &listener);
    void remKeyboardListener(KeyboardListenerPtr &listener);
    void pollAsyncInputs();
    void connectKeyboard(KeyboardPtrWeak &in_keyboard);
    void setAsyncInputHook(std::map<input_event, int> *hook);
    void connectEngine(Engine *in_engine);
    void onMessage(const std::string &in_message);
    bool running = true;

private:
    void render();
    void get_input();
    void do_debug_ui();
    void on_click(int x, int y, WidgetPtr &widget);
    void sort_widgets();
    bool mouse_pressed = false;
    sf::RenderWindow window;
    sf::VideoMode video_mode;
    sf::Vector2i mouse_position;
    keyboardlistenerList keyboard_listeners;
    EntityPtr root_entity = std::make_shared<Entity>("root");
    WidgetPtr root_widget = std::make_shared<Widget>();
    KeyboardPtrWeak keyboard;
    Widget *grabbed_widget = nullptr;
    bool widget_changed = false;
    Engine *engine = nullptr;
    bool widget_grabbed = false;
    std::mutex viewer_mutex;
    sf::Clock clock;
    sf::Time time;
    float fps = 0;
    void calc_fps();
};
} // namespace gamelib2
