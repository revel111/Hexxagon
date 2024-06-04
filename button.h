#pragma once

#include <SFML/Graphics.hpp>

class Button {
public:
    /**
     * Constructor used for each button in this project.
     * @param text
     * @param radius
     * @param charSize
     * @param back
     * @param pos
     * @param font
     */
    Button(const std::string &text, const float &radius, const int &charSize, const sf::Color &back,
           const sf::Vector2f &pos, const sf::Font &font, int angles);

    Button();

    auto getText() -> sf::Text &;

    auto getDefColor() -> sf::Color &;

    auto setDefColor(const sf::Color &defColor) -> void;

    /**
     * Function for position setting.
     * @param pos
     * @param width for position adjustment by width
     * @param height for position adjustment by height
     * @return void
     */
    auto setPosition(const sf::Vector2f &pos, float width, float height) -> void;

    /**
     * Function for centralizing text of a button.
     * @return void
     */
    auto centralizeText() -> void;

    /**
     * Function for drawing a button.
     * @param window
     * @return void
     */
    auto drawBut(sf::RenderWindow &window) -> void;

    /**
     * Detect whether mouse is over specific button.
     * @param window
     * @return bool
     */
    auto isMouseOver(sf::RenderWindow &window) -> bool;

    /**
     * Color effect for buttons in the menu and for button "save" in the game
     * @param window
     * @return void
     */
    auto colorButMenu(sf::RenderWindow &window) -> void;


private:
    sf::CircleShape button;
    sf::Text text;
    sf::Color defColor;
    int angles;
};