#include "map.h"

auto Map::initializeMap(sf::RenderWindow &window, const sf::Font &font) -> void {
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
                    button->setText("X");
                    button->setTextColor(sf::Color(128,128,128));
                    button->setDefColor(sf::Color(128,128,128));
                    break;
                case 1:
                    button->setText("O");
                    button->setDefColor(sf::Color::White);
                    break;
                case 2:
                    button->setText("1");
                    button->setTextColor(sf::Color::Blue);
                    button->setDefColor(sf::Color::Blue);
                    break;
                case 3:
                    button->setText("2");
                    button->setTextColor(sf::Color::Cyan);
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

auto Map::drawMap(sf::RenderWindow &window) -> void {
    for (auto & i : mapBut) {
        for (const auto & j : i) {
            j->drawBut(window);
        }
    }
}

auto Map::makeMove(sf::RenderWindow &window) -> void {
    for (auto & i : mapBut) {
        for (const auto & j : i) {
            j->colorButGame(window);
        }
    }
}