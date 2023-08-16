#include "butMenu.h"

ButtonMenu::ButtonMenu(const std::string &text, const sf::Vector2f &size, const int &charSize, const sf::Color &back) {
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(charSize);
    button.setSize(size);
    button.setFillColor(back);
}

void ButtonMenu::setDefColor(const sf::Color &defColor) {
    ButtonMenu::defColor = defColor;
}

auto ButtonMenu::setFont(const sf::Font &font) -> void {
    text.setFont(font);
}

auto ButtonMenu::setBackColor(const sf::Color &color) -> void {
    button.setFillColor(color);
}

auto ButtonMenu::setTextColor(const sf::Color &color) -> void {
    text.setFillColor(color);
}

auto ButtonMenu::setPosition(const sf::Vector2f &pos) -> void {
    button.setPosition(pos);

    auto xPos = (pos.x + button.getGlobalBounds().width / 7) - (text.getGlobalBounds().width / 3);
    auto yPos = (pos.y + button.getGlobalBounds().height / 3) - (text.getGlobalBounds().height / 3);

    text.setPosition(xPos, yPos);
}

auto ButtonMenu::setText(const std::string &text) -> void {
    this->text.setString(text);
}

auto ButtonMenu::drawBut(sf::RenderWindow &window) -> void {
    window.draw(button);
    window.draw(text);
}

auto ButtonMenu::isMouseOver(sf::RenderWindow &window) -> bool {
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

auto ButtonMenu::initializeBut(const sf::Vector2f &pos, const sf::Font &font) -> void {
    this->setPosition(pos);
    this->setFont(font);
}

auto ButtonMenu::colorButMenu(sf::RenderWindow &window) -> void {
    if (this->isMouseOver(window)) {
        this->setBackColor(sf::Color::White);
        this->setTextColor(sf::Color(128, 128, 128));
    } else {
        this->setBackColor(sf::Color(128, 128, 128));
        this->setTextColor(sf::Color::White);
    }
}

auto ButtonMenu::colorButGame(sf::RenderWindow &window) -> void {
    if (this->isMouseOver(window))
        this->setTextColor(sf::Color::Green);
    else
        this->setTextColor(defColor);
}