#pragma once

#include "button.h"
#include "gamestate.h"
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
#include <map>
#include <ctime>
#include <filesystem>

class Game {
public:
    explicit Game(bool mode);

    Game(const std::vector<std::vector<int>> &mapInt, bool mode, bool turn, const sf::Time &timer);

    auto getTimer() -> sf::Time &;

    auto initializeMap(sf::RenderWindow &window, const sf::Font &font) -> void;

    auto drawMap(sf::RenderWindow &window) -> void;

    auto makeMove(sf::RenderWindow &window) -> void;

    auto checkEnd() -> bool;

    auto checkSelected() -> bool;

    auto colorButGame(sf::RenderWindow &window, int y, int x) -> void;

    auto checkMove(int y, int x) -> void;

    auto counter(int ch) -> std::string;

    auto aiMakeMove(/*std::pair<const std::vector<int>, int> window*/) -> void;

    auto findSelected() -> std::vector<int>;

    static auto saveInFile(int first, int second) -> void;

    static auto readFile() -> std::string;

    auto disableColor(bool ch) -> void;

    auto colorPossible(/*int y, int x*/) -> void;

    auto saveGame() -> void;

    static auto loadGame(const std::string &path) -> Game;

    static auto loadGameBut(const sf::Font &font) -> std::vector<std::unique_ptr<Button>>;

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
//    std::vector<std::vector<int>> mapInt = {{-1, -1, 3,  -1, -1},
//                                            {-1, 1,  -1, 1,  -1},
//                                            {1,  1,  1,  -1, -1},
//                                            {1,  1,  1,  1,  -1},
//                                            {2,  1,  1,  1,  2},
//                                            {1,  1,  1,  1,  -1},
//                                            {1,  1,  0,  1,  1},
//                                            {1,  1,  1,  1,  -1},
//                                            {1,  1,  1,  1,  1},
//                                            {1,  0,  1,  0,  -1},
//                                            {1,  1,  1,  1,  1},
//                                            {1,  1,  1,  1,  -1},
//                                            {3,  1,  1,  1,  3},
//                                            {1,  1,  1,  1,  -1},
//                                            {1,  1,  1,  -1, -1},
//                                            {1,  1,  -1, -1, -1},
//                                            {2,  -1, -1, -1, -1},
//    };
//    std::vector<std::vector<int>> mapInt = {{3},
//                                            {1, 1},
//                                            {1, 1, 1},
//                                            {2, 1, 1, 2}
//    };
//    std::vector<std::vector<int>> mapInt = {{3, 1, 1, 1, 3},
//                                            {1, 1, 1, 1},
//                                            {1, 1, 1, 1, 1},
//                                            {1, 1, 1, 1},
//                                            {2, 1, 1, 1, 2},
//    };
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

    sf::Time timer = sf::seconds(0);
    bool mode;
    bool turn;
    std::vector<std::vector<std::unique_ptr<Button>>> mapBut;
};