#pragma once

#include <SFML/Graphics.hpp>

class Button {
public:
    Button(const std::string &text);

    auto setFont(const sf::Font &font) -> void;

    auto setBackColor(const sf::Color &color) -> void;

    auto setTextColor(const sf::Color &color) -> void;

    auto setPosition(const sf::Vector2f &pos) -> void;

    auto drawBut(sf::RenderWindow &window) -> void;

    auto isMouseOver(sf::RenderWindow &window) -> bool;

    static auto initializeBut(Button &button, const sf::Vector2f &pos, const sf::Font &font) -> void;

    static auto colorBut(Button &button, sf::RenderWindow &window) -> void;

private:
    sf::RectangleShape button;
    sf::Text text;
};