#include "buttonFuncs.h"

Button::Button(const std::string &text) {
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(20);
    button.setSize({125, 65});
    button.setFillColor(sf::Color(128, 128, 128));
}

auto Button::setFont(const sf::Font &font) -> void {
    text.setFont(font);
}

auto Button::setBackColor(const sf::Color &color) -> void {
    button.setFillColor(color);
}

auto Button::setTextColor(const sf::Color &color) -> void {
    text.setFillColor(color);
}

auto Button::setPosition(const sf::Vector2f &pos) -> void {
    button.setPosition(pos);

    auto xPos = (pos.x + button.getGlobalBounds().width / 7) - (text.getGlobalBounds().width / 3);
    auto yPos = (pos.y + button.getGlobalBounds().height / 3) - (text.getGlobalBounds().height / 3);

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

auto Button::initializeBut(/*std::vector<Button>*/Button &button, const sf::Vector2f &pos, const sf::Font &font) -> void {
//    auto font = sf::Font{};
//    font.loadFromFile("CALISTB.ttf");
//    for (Button button : buttons) {
        button.setPosition(pos);
        button.setFont(font);
//        pos.x += 300;
//    }
}

auto Button::colorBut(Button &button, sf::RenderWindow &window) -> void {
    if (button.isMouseOver(window)) {
        button.setBackColor(sf::Color::White);
        button.setTextColor(sf::Color(128, 128, 128));
    } else {
        button.setBackColor(sf::Color(128, 128, 128));
        button.setTextColor(sf::Color::White);
    }
}