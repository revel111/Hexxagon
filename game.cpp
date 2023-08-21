#include "game.h"

Game::Game(bool mode) {
    this->mode = mode;
    turn = false;
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
            auto button = std::make_unique<ButtonMenu>("", sf::Vector2f(50, 25), 15, sf::Color::Black);
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
    for (auto i = 0; i < mapBut.size(); i++)
        for (auto j = 0; j < mapBut[i].size(); j++)
            colorButGame(window, mapBut[i][j], j, i);
}

auto Game::checkEnd() -> bool {
    for (auto &i: mapBut)
        for (const auto &j: i)
            if (j->getText().getString() == "O")
                return false;
            else if (j->getText().getString() == "1" || j->getText().getString() == "2") {

            }

    return true;
}

auto Game::checkSelected() -> bool {
    for (auto &i: mapBut)
        for (const auto &j: i)
            if (j->getText().getFillColor() == sf::Color::Green)
                return true;

    return false;
}

auto Game::colorButGame(sf::RenderWindow &window, std::unique_ptr<ButtonMenu> &button, int x, int y) -> void {
    if (button->isMouseOver(window) && checkSelected())
        if (button->getText().getFillColor() == sf::Color::Green)
            button->getText().setFillColor(button->getDefColor());
        else
            checkMove(button, x, y);
    else if (button->isMouseOver(window))
        if ((turn && button->getText().getString() == "2") || (!turn && button->getText().getString() == "1"))
            button->getText().setFillColor(sf::Color::Green);
}

auto Game::checkMove(std::unique_ptr<ButtonMenu> &button, int x, int y) -> void {
    auto selectedX = 0, selectedY = 0;

    for (auto i = 0; i < mapBut.size(); i++)
        for (auto j = 0; j < mapBut[i].size(); j++)
            if (mapBut[i][j]->getText().getFillColor() == sf::Color::Green) {
                selectedX = j, selectedY = i;
                mapBut[selectedY][selectedX]->getText().setFillColor(mapBut[selectedY][selectedX]->getDefColor());
            }

    if (button->getText().getString() == "O" && ((abs(selectedX - x) <= 2) && (abs(selectedY - y) <= 4))) {
        if ((abs(selectedX - x) == 2) || ((abs(selectedY - y)) == 4) || ((abs(selectedY - y)) == 3)) {
            mapBut[selectedY][selectedX]->getText().setString("O");
            mapBut[selectedY][selectedX]->setDefColor(sf::Color::White);
            mapBut[selectedY][selectedX]->getText().setFillColor(sf::Color::White);
        }

        std::vector<std::vector<int>> offsetEnemy = {
                {-2, 0},
                {-1, -1},
                {-1, 0},
                {-1, 1},
                {0,  -1},
                {1,  -1},
                {0,  1},
                {1,  0},
                {1,  1},
                {2,  0}
        };

        for (const auto &offset: offsetEnemy) {
            auto newY = y + offset[0];
            auto newX = x + offset[1];

            if (mapBut[newY].size() == 5) {
                if ((offset[0] == 1 && offset[1] == -1) ||
                    (offset[0] == -1 && offset[1] == -1)) {
                    continue;
                }
            } else if (mapBut[newY].size() == 4)
                if ((offset[0] == -1 && offset[1] == 1) ||
                    (offset[0] == 1 && offset[1] == 1)) {
                    continue;
                }

            if (newX >= 0 && newY < mapBut.size() && newY >= 0 && newX < mapBut[newY].size()) {
                if (mapBut[newY][newX]->getText().getString() == "2" && !turn) {
                    mapBut[newY][newX]->getText().setString("1");
                    mapBut[newY][newX]->setDefColor(sf::Color::Blue);
                    mapBut[newY][newX]->getText().setFillColor(sf::Color::Blue);
                } else if (mapBut[newY][newX]->getText().getString() == "1" && turn) {
                    mapBut[newY][newX]->getText().setString("2");
                    mapBut[newY][newX]->setDefColor(sf::Color::Cyan);
                    mapBut[newY][newX]->getText().setFillColor(sf::Color::Cyan);
                }
            }
        }

        if (turn) {
            button->getText().setString("2");
            button->getText().setFillColor(sf::Color::Cyan);
            button->setDefColor(sf::Color::Cyan);
            turn = false;
        } else {
            button->getText().setString("1");
            button->getText().setFillColor(sf::Color::Blue);
            button->setDefColor(sf::Color::Blue);
            turn = true;
        }
    }
}

auto Game::counter(bool ch) -> std::string {
    auto count = 0;
    for (auto &i: mapBut)
        for (const auto &j: i)
            if ((j->getText().getString() == "1" && ch) || (j->getText().getString() == "2" && !ch))
                count++;

    return std::to_string(count);
}