#pragma once

#include "butMenu.h"
#include <vector>
#include <memory>
#include <valarray>


class Game {
public:
    Game(bool mode);

    auto initializeMap(sf::RenderWindow &window, const sf::Font &font) -> void;

    auto drawMap(sf::RenderWindow &window) -> void;

    auto makeMove(sf::RenderWindow &window) -> void;

    auto checkEnd() -> bool;

    auto checkSelected() -> bool;

    auto colorButGame(sf::RenderWindow &window, std::unique_ptr<ButtonMenu> &button) -> void;

private:
    std::vector<std::vector<int>> mapInt = {{3},
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

    int you;
    int enemy;
    bool mode;
    bool turn;
    std::vector<std::vector<std::unique_ptr<ButtonMenu>>> mapBut;
};