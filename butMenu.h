#pragma once

#include <SFML/Graphics.hpp>

class ButtonMenu {
public:
    ButtonMenu(const std::string &text, const sf::Vector2f &size, const int &charSize, const sf::Color &back);

    void setDefColor(const sf::Color &defColor);

    auto setBackColor(const sf::Color &color) -> void;

    auto setTextColor(const sf::Color &color) -> void;

    auto setPosition(const sf::Vector2f &pos) -> void;

    auto setText(const std::string &text) -> void;

    auto drawBut(sf::RenderWindow &window) -> void;

    auto isMouseOver(sf::RenderWindow &window) -> bool;

    auto initializeBut(const sf::Vector2f &pos, const sf::Font &font) -> void;

    auto colorButMenu(sf::RenderWindow &window) -> void;

    auto colorButGame(sf::RenderWindow &window) -> void;

private:
    sf::RectangleShape button;
    sf::Text text;
    sf::Color defColor;

    auto setFont(const sf::Font &font) -> void;
};