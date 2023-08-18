#include "game.h"

Game::Game(bool mode) {
    this->mode = mode;
    turn = true;
    you = 0;
    enemy = 0;
}

auto Game::initializeMap(sf::RenderWindow &window, const sf::Font &font) -> void {
    mapBut.resize(mapInt.size());
    auto maxColumns = 0;

    for (const auto &row: mapInt)
        if (row.size() > maxColumns)
            maxColumns = row.size();

    auto startX = (1200 - (50 * 1.5f) * maxColumns) / 2;
    auto startY = (800 - (std::sqrt(3.0f) * 25) * (mapInt.size() + 0.5)) / 2;

    for (auto i = 0; i < mapInt.size(); i++) {
        auto currentStartX = startX;
        switch (mapInt[i].size()) {
            case 1:
                currentStartX += 150;
                break;
            case 2:
                currentStartX += 110;
                break;
            case 3:
                currentStartX += 75;
                break;
            case 4:
                currentStartX += 35;
                break;
        }

        for (auto j = 0; j < mapInt[i].size(); j++) {
            auto button = std::make_unique<ButtonMenu>("", sf::Vector2f(50, 15), 15, sf::Color::Black);
            switch (mapInt[i][j]) {
                case 0:
                    button->getText().setString("X");
                    button->getText().setFillColor(sf::Color(128, 128, 128));
                    button->setDefColor(sf::Color(128, 128, 128));
                    break;
                case 1:
                    button->getText().setString("O");
                    button->setDefColor(sf::Color::White);
                    break;
                case 2:
                    button->getText().setString("1");
                    button->getText().setFillColor(sf::Color::Blue);
                    button->setDefColor(sf::Color::Blue);
                    break;
                case 3:
                    button->getText().setString("2");
                    button->getText().setFillColor(sf::Color::Cyan);
                    button->setDefColor(sf::Color::Cyan);
                    break;
            }
            sf::Vector2f pos = {currentStartX + j * (50 * 1.5f),
                                static_cast<float>(startY + i * (std::sqrt(3.0f) * 25) + 1)};
            button->initializeBut(pos, font);
            mapBut[i].push_back(std::move(button));
            mapBut[i][j]->drawBut(window);
        }
    }
}

auto Game::drawMap(sf::RenderWindow &window) -> void {
    for (auto &i: mapBut)
        for (const auto &j: i)
            j->drawBut(window);
}

auto Game::makeMove(sf::RenderWindow &window) -> void {
    for (auto &i: mapBut)
        for (auto &j: i)
            colorButGame(window, j);
}

auto Game::checkEnd() -> bool {
    for (auto &i: mapBut)
        for (const auto &j: i)
            if (j->getText().getString() == "O")
                return false;

    return true;
}

auto Game::checkSelected() -> bool {
    for (auto &i: mapBut)
        for (const auto &j: i)
            if (j->getText().getFillColor() == sf::Color::Green)
                return true;

    return false;
}

auto Game::colorButGame(sf::RenderWindow &window, std::unique_ptr<ButtonMenu> &button) -> void {
    if (button->isMouseOver(window) && Game::checkSelected())
        if (button->getText().getFillColor() == sf::Color::Green)
            button->getText().setFillColor(button->getDefColor());
        else if (turn) {
            button->getText().setString("2");
            turn = false;
        } else {
            button->getText().setString("1");
            turn = true;
        }
    else if (button->isMouseOver(window)) {
        if (turn && button->getText().getString() == "2")
            button->getText().setFillColor(sf::Color::Green);
        else if (!turn && button->getText().getString() == "1")
            button->getText().setFillColor(sf::Color::Green);
        else
            button->getText().setFillColor(button->getDefColor());
    } else
        button->getText().setFillColor(button->getDefColor());
}