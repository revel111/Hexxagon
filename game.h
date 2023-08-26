#pragma once

#include "button.h"
#include <vector>
#include <memory>
#include <sstream>
#include <valarray>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ranges>
#include <regex>

class Game {
public:
    explicit Game(bool mode);

    auto initializeMap(sf::RenderWindow &window, const sf::Font &font) -> void;

    auto drawMap(sf::RenderWindow &window) -> void;

    auto makeMove(sf::RenderWindow &window) -> void;

    auto checkEnd() -> bool;

    auto checkSelected() -> bool;

    auto colorButGame(sf::RenderWindow &window, std::unique_ptr<Button> &button, int x, int y) -> void;

    auto checkMove(std::unique_ptr<Button> &button, int x, int y) -> void;

    auto counter(int ch) -> std::string;

    auto aiMakeMove(sf::RenderWindow &window) -> void;

    static auto saveInFile(int first, int second) -> void;

    static auto readFile() -> std::string;

private:
//    std::vector<std::vector<int>> mapInt = {{3},
//                                            {1, 1},
//                                            {1, 1, 1},
//                                            {1, 1, 1, 1},
//                                            {2, 1, 1, 1, 2},
//                                            {1, 1, 1, 1},
//                                            {1, 1, 0, 1, 1},
//                                            {1, 1, 1, 1},
//                                            {1, 1, 1, 1, 1},
//                                            {1, 0, 0, 1},
//                                            {1, 1, 1, 1, 1},
//                                            {1, 1, 1, 1},
//                                            {3, 1, 1, 1, 3},
//                                            {1, 1, 1, 1},
//                                            {1, 1, 1},
//                                            {1, 1},
//                                            {2}
//    };
    std::vector<std::vector<int>> mapInt = {{3},
                                            {1, 1},
                                            {1, 1, 1},
                                            {2, 1, 1, 2}
    };
//    std::vector<std::vector<int>> mapInt = {{3, 1, 1, 1, 3},
//                                            {1, 1, 1, 1},
//                                            {1, 1, 1, 1, 1},
//                                            {1, 1, 1, 1},
//                                            {2, 1, 1, 1, 2},
//    };

    bool mode;
    bool turn;
    std::vector<std::vector<std::unique_ptr<Button>>> mapBut;
};