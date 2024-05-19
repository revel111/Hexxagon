#include "button.h"

Button::Button(const std::string &text, const sf::Vector2f &size, const int &charSize, const sf::Color &back,
               const sf::Vector2f &pos, const sf::Font &font, float width, float height) {
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(charSize);
    button.setSize(size);
    button.setFillColor(back);
    setPosition(pos, width, height);
    this->text.setFont(font);
}

Button::Button() = default;

auto Button::getText() -> sf::Text & {
    return text;
}

auto Button::getButton() -> sf::RectangleShape & {
    return button;
}

auto Button::getDefColor() -> sf::Color & {
    return defColor;
}

auto Button::setDefColor(const sf::Color &defColor) -> void {
    this->defColor = defColor;
}

auto Button::setPosition(const sf::Vector2f &pos, float width, float height) -> void {
    button.setPosition(pos);

    auto xPos = (pos.x + button.getGlobalBounds().width / width) - (text.getGlobalBounds().width / width);
    auto yPos = (pos.y + button.getGlobalBounds().height / height) - (text.getGlobalBounds().height / height);

    text.setPosition(xPos, yPos);
}

auto Button::drawBut(sf::RenderWindow &window) -> void {
    window.draw(button);
    window.draw(text);
}

auto Button::isMouseOver(sf::RenderWindow &window) -> bool {
    auto xMouse = sf::Mouse::getPosition(window).x;
    auto yMouse = sf::Mouse::getPosition(window).y;

    auto xButPos = button.getPosition().x;
    auto yButPos = button.getPosition().y;

    auto butXPosWid = button.getPosition().x + button.getLocalBounds().width;
    auto butYPosHei = button.getPosition().y + button.getLocalBounds().height;

    if (xMouse < butXPosWid && xMouse > xButPos && yMouse < butYPosHei && yMouse > yButPos)
        return true;

    return false;
}

auto Button::colorButMenu(sf::RenderWindow &window) -> void {
    if (isMouseOver(window)) {
        button.setFillColor(sf::Color::White);
        text.setFillColor(sf::Color(128, 128, 128));
    } else {
        button.setFillColor(sf::Color(128, 128, 128));
        text.setFillColor(sf::Color::White);
    }
}

//auto Button::colorButtonGame(sf::Color &color) -> void {
//    text.setFillColor(color);
//    button.setOutlineColor(color);
//}