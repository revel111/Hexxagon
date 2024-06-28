#include "button.h"

Button::Button(const std::string &text, const float &radius, const int &charSize, const sf::Color &back,
               const sf::Vector2f &pos, const sf::Font &font, int angles) {
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(charSize);
    this->text.setFont(font);

    button.setRadius(radius);
    button.setPointCount(angles);
    button.setFillColor(back);
    button.setOutlineThickness(2.0f);
    button.setPosition(pos);

    if (angles == 4)
        button.setRotation(45);
    else
        button.setRotation(90);

    centralizeText();
}

Button::Button() = default;

auto Button::getText() -> sf::Text & {
    return text;
}


auto Button::setDefColor(const sf::Color &defColor) -> void {
    this->defColor = defColor;
}

auto Button::drawBut(sf::RenderWindow &window) const -> void {
    window.draw(button);
    window.draw(text);
}

auto Button::isMouseOver(sf::RenderWindow &window) -> bool {
    auto mousePosWindow = sf::Mouse::getPosition(window);
    auto mousePosView = window.mapPixelToCoords(mousePosWindow);

    return button.getGlobalBounds().contains(mousePosView);
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

auto Button::centralizeText() -> void {
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    sf::FloatRect textBounds = text.getLocalBounds();

    float xCenter = buttonBounds.left + (buttonBounds.width / 2.0f);
    float yCenter = buttonBounds.top + (buttonBounds.height / 2.0f);

    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(xCenter, yCenter);
}

auto Button::getTextString() -> std::basic_string<char> {
    return text.getString().toAnsiString();
}

auto Button::color(const sf::Color &color) -> void {
    text.setFillColor(color);
    button.setOutlineColor(color);
}

auto Button::colorDefault() -> void {
    text.setFillColor(defColor);
    button.setOutlineColor(defColor);
}