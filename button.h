#pragma once

#include <SFML/Graphics.hpp>

class Button {
public:
    Button(const std::string &text, const sf::Vector2f &size, const int &charSize, const sf::Color &back, const sf::Vector2f &pos, const sf::Font &font, float width, float height);

    sf::Text &getText();

    sf::RectangleShape &getButton();

    sf::Color &getDefColor();

    void setDefColor(const sf::Color &defColor);

    auto setPosition(const sf::Vector2f &pos, float width, float height) -> void;

    auto drawBut(sf::RenderWindow &window) -> void;

    auto isMouseOver(sf::RenderWindow &window) -> bool;

    auto initializeBut(const sf::Vector2f &pos, const sf::Font &font, float width, float height) -> void;

    auto colorButMenu(sf::RenderWindow &window) -> void;

private:
    sf::RectangleShape button;
    sf::Text text;
    sf::Color defColor;
};