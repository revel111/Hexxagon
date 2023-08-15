#include <valarray>
#include "map.h"

std::vector<std::vector<int>> Map::map = {
        {3},
        {1, 1},
        {1, 1, 1},
        {1, 1, 1, 1},
        {2, 1, 1, 1, 2},
        {1, 1, 1, 1},
        {1, 1, 0, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1},
        {3, 1, 1, 1, 3},
        {1, 1, 1, 1},
        {1, 1, 1},
        {1, 1},
        {2}
};

auto Map::draw(sf::RenderWindow &window, const sf::Font &font) -> void {
    auto maxColumns = 0;

    for (const auto &row: map)
        if (row.size() > maxColumns)
            maxColumns = row.size();

    auto startX = (1200 - (50 * 1.5f) * maxColumns) / 2;
    auto startY = (800 - (std::sqrt(3.0f) * 25) * (map.size() + 0.5)) / 2;

    for (auto i = 0; i < map.size(); i++) {
        auto currentStartX = startX;
        switch (map[i].size()) {
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

        for (auto j = 0; j < map[i].size(); j++) {
            auto button = Button("", {50, 15}, 15, sf::Color::Black);
            switch (map[i][j]) {
                case 0:
                    button.setText("X");
                    break;
                case 1:
                    button.setText("O");
                    break;
                case 2:
                    button.setText("1");
                    break;
                case 3:
                    button.setText("2");
                    break;
            }
            sf::Vector2f pos = {currentStartX + j * (50 * 1.5f),
                                static_cast<float>(startY + i * (std::sqrt(3.0f) * 25) + 1)};
            Button::initializeBut(button, pos, font);
            button.drawBut(window);
        }
    }
}
