#pragma once

#include <SFML/Graphics.hpp>

class Button {
public:
    Button(const std::string &text, const sf::Vector2f &size, const int &charSize, const sf::Color &back);

    auto setPosition(const sf::Vector2f &pos) -> void;

    auto setText(const std::string &text) -> void;

    auto drawBut(sf::RenderWindow &window) -> void;

    auto isMouseOver(sf::RenderWindow &window) -> bool;

    static auto initializeBut(Button &button, const sf::Vector2f &pos, const sf::Font &font) -> void;

    static auto colorBut(Button &button, sf::RenderWindow &window) -> void;

private:
    sf::RectangleShape button;
    sf::Text text;

    auto setBackColor(const sf::Color &color) -> void;

    auto setTextColor(const sf::Color &color) -> void;

    auto setFont(const sf::Font &font) -> void;
};