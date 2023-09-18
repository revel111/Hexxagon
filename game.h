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
    /**
    * Constructor for creating game when user creates new one.
    * @param mode
    */
    explicit Game(bool mode);

    /**
    * Constructor for creating game when user loads one.
    * @param mapInt
    * @param mode
    * @param turn
    * @param timer
    */
    Game(const std::vector<std::vector<int>> &mapInt, bool mode, bool turn, const sf::Time &timer);

    auto getTimer() -> sf::Time &;

    /**
    * Function for first map drawing i.e. when game board is drawing first time.
    * @param window
    * @param font
    * @return void
    */
    auto initializeMap(sf::RenderWindow &window, const sf::Font &font) -> void;

    /**
    * Function for just usual map drawing, after first drawing.
    * @param window
    * @return void
    */
    auto drawMap(sf::RenderWindow &window) -> void;

    /**
    * Function which defines if there is any action related with game board which has to be proceed.
    * @param window
    * @return void
    */
    auto makeMove(sf::RenderWindow &window) -> void;

    /**
    * Function which simply checks whether game is ended or not.
    * @return bool
    */
    auto checkEnd() -> bool;

    /**
    * Auxiliary function which defines whether there is selected pawn.
    * @return bool
    */
    auto checkSelected() -> bool;

    /**
    * Function which proceeds actions happened with the game board.
    * @param window
    * @param y
    * @param x
    * @return void
    */
    auto colorButGame(sf::RenderWindow &window, int y, int x) -> void;

    /**
    * Function which allows to proceed a move if it is possible.
    * @param y
    * @param x
    * @return void
    */
    auto checkMove(int y, int x) -> void;

    /**
    * Function which colors specific free places where pawn can move.
    * @param y
    * @param x
    * @return void
    */
    auto colorPossible(int y, int x) -> void;

    /**
    * Function which simply counts amount of "1" pawns, "2" pawns and "0" i.e. free places.
    * @param ch (choice for counting specific objects)
    * @return std::string
    */
    auto counter(int ch) -> std::string;

    /**
    * Function defined for computer move choosing.
    * @return void
    */
    auto aiMakeMove() -> void;

    /**
    * Function for proceeding new score and if it is new high score, putting it into text file "results".
    * This file read in the menu with high score.
    * @param player1
    * @param player2
    * @return void
    */
    static auto saveInFile(int first, int second) -> void;

    /**
    * Function defined for displaying high scores in the corresponding menu.
    * @return std::string
    */
    static auto readFile() -> std::string;

    /**
    * Function for coloring buttons their default color.
    * @param ch
    * @return void
    */
    auto disableColor(bool ch) -> void;

    /**
    * Function for saving current game into text file. Game can be loaded in the future in the corresponding menu.
    * @return void
    */
    auto saveGame() -> void;

    /**
    * Function for loading a game from the specific file, which was chosen by the user.
    * @param path
    * @return Game
    */
    static auto loadGame(const std::string &path) -> Game;

    /**
    * Auxiliary function defined for fast buttons loading from the "savings" folder.
    * @param font
    * @return
    */
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