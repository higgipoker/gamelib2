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
#include <SFML/Graphics/RenderWindow.hpp>
#include "../widgets/widget.hpp"
#include "../imgui/imgui.h"

namespace gamelib2 {
class mygui {
 public:
  bool visible = false;
  bool check1 = false;
  bool check2 = false;
  std::string window_title = "debug";
  sf::Rect<float> rect;
  float alpha = 1.0;
  sf::Clock deltaClock;
  ImGuiWindowFlags flags =
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
  bool hover(int x, int y) { return rect.contains(x, y) && visible; }
  void showSpriteFrame(Widget& widget);
};  // namespace mygui
}  // namespace gamelib2
