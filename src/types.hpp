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
#include <memory>
#include <vector>

namespace gamelib2 {

class Entity;
class Widget;
class Sprite;
class KeyboardListener;
class Engine;
class Viewer;
class Keyboard;
class Controller;

using WidgetPtr = std::shared_ptr<Widget>;
using WidgetWeakPtr = std::weak_ptr<Widget>;
using WidgetUniquePtr = std::unique_ptr<Widget>;
using WidgetList = std::vector<Widget *>;
using SpritePointer = std::shared_ptr<Sprite>;
using KeyboardListenerPtr = std::shared_ptr<KeyboardListener>;
using keyboardlistenerList = std::vector<KeyboardListenerPtr>;
using EnginePtr = std::shared_ptr<Engine>;
using ViewerPtr = std::shared_ptr<Viewer>;
using EntityPtr = std::shared_ptr<Entity>;
using EntityWeakPtr = std::weak_ptr<Entity>;
using EntityUniquePtr = std::unique_ptr<Entity>;
using EntityList = std::vector<EntityPtr>;
using KeyboardPtr = std::shared_ptr<Keyboard>;

} // namespace gamelib2
