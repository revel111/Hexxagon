#pragma once

#include "butMenu.h"
#include <vector>
#include <memory>
#include <valarray>


class Map {
public:
    auto initializeMap(sf::RenderWindow &window, const sf::Font &font) -> void;

    auto drawMap(sf::RenderWindow &window) -> void;

    auto makeMove(sf::RenderWindow &window) -> void;

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
    std::vector<std::vector<std::unique_ptr<ButtonMenu>>> mapBut;
};