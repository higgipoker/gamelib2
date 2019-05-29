#include "label.hpp"
#include <iostream>
#include <sstream>
namespace gamelib2 {

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Label::Label(const std::string &fontname) {
    // todo font factory
    if (!font.loadFromFile(fontname)) {
        std::cout << "error loading font: " << fontname << std::endl;
    } else {
        text.setFont(font);
        text.setCharacterSize(8);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Regular);
    }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Label::render(sf::RenderTarget &target) {
    target.draw(text);
    Widget::render(target);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Label::setPosition(float x, float y) {
    text.setPosition(x, y);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Label::setText(std::string l) {
    label = std::move(l);
    text.setString(label);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Label::setText(int a_number) {
    std::ostringstream s;
    s << a_number;
    label = std::move(s.str());
    text.setString(label);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Label::setColor(sf::Color c) {
    text.setFillColor(c);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Label::setSize(int s) {
    text.setCharacterSize(s);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
sf::FloatRect Label::bounds() {
    return text.getGlobalBounds();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Label::setCenter(int x, int y) {
    text.setPosition(x - text.getGlobalBounds().width / 2,
                     y - text.getGlobalBounds().height / 2);
}

} // namespace gamelib2
