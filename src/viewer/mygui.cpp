#include "mygui.hpp"
#include <iostream>
#include <sstream>

namespace gamelib2 {
void mygui::showSpriteFrame(Widget &widget) {
    /////////////////////////////////////////////////////////////////////////////
    /// name
    /////////////////////////////////////////////////////////////////////////////
    ImGui::NewLine();
    ImGui::Bullet();
    std::ostringstream name;
    name << widget.getName() << " (" << static_cast<int>(widget.position().x)
         << ", " << static_cast<int>(widget.position().y) << ")";
    ImGui::Text("%s", name.str().c_str());

    /////////////////////////////////////////////////////////////////////////////
    /// animations dropdown
    /////////////////////////////////////////////////////////////////////////////
    static int item_current = 0;
    std::vector<const char *> items;
    std::map<SpriteAnimation *, int> anim_map;
    size_t i = 0;
    for (auto &animation : widget.animations) {
        items.push_back(animation.first.c_str());
        anim_map.insert(std::make_pair(&animation.second, i++));
    }
    items.push_back("none");

    // need to get the index of active animation
    SpriteAnimation *anim = widget.active_animation();
    if (anim) {
        item_current = anim_map[anim];
    } else {
        item_current = static_cast<int>(items.size() - 1);
    }

    ImGui::Combo("animation", &item_current, &items[0],
                 static_cast<int>(items.size()));
    const std::string anim_name(items[static_cast<unsigned int>(item_current)]);
    if (anim_name == "none") {
        widget.stopAnimation();
    } else {
        widget.startAnimation(anim_name);
    }

    /////////////////////////////////////////////////////////////////////////////
    /// scaling
    /////////////////////////////////////////////////////////////////////////////
    static float scale = 1.0f;
    ImGui::SliderFloat("scale", &scale, 0.0f, 10.0f, "%.1f");
    widget.scale(scale, scale);

    // ImGui::SameLine();
}
} // namespace gamelib2
