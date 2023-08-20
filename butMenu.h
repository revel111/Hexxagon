#pragma once

#include <SFML/Graphics.hpp>

class ButtonMenu {
public:
    ButtonMenu(const std::string &text, const sf::Vector2f &size, const int &charSize, const sf::Color &back);

    sf::Text &getText();

    sf::RectangleShape &getButton();

     sf::Color &getDefColor();

    void setDefColor(const sf::Color &defColor);

    auto setPosition(const sf::Vector2f &pos) -> void;

    auto drawBut(sf::RenderWindow &window) -> void;

    auto isMouseOver(sf::RenderWindow &window) -> bool;

    auto initializeBut(const sf::Vector2f &pos, const sf::Font &font) -> void;

    auto colorButMenu(sf::RenderWindow &window) -> void;

private:
    sf::RectangleShape button;
    sf::Text text;
    sf::Color defColor;
};