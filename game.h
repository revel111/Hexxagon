#pragma once

#include "button.h"
#include "gamestate.h"
#include "hex.h"
#include "Coords.h"
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

using std::string, std::vector, std::pair, std::unique_ptr;

class Game {
public:
    /**
    * Constructor for creating game when user creates new one.
    * @param mode
    */
    explicit Game(bool mode);

    Game();

    /**
    * Constructor for creating game when user loads one.
    * @param mapInt
    * @param mode
    * @param turn
    * @param timer
    */
    Game(const vector<vector<int>> &mapInt, bool mode, bool turn, const sf::Time &timer);

    auto getTimer() -> sf::Time &;

    /**
    * Function for first map drawing i.e. when game board is drawing first time.
    * @param window
    * @param font
    * @return void
    */
    auto initializeMap(sf::RenderWindow &window, const sf::Font &font) -> void;
    /**
     * Function for creating all coordinates for the game
     * @return std::deque<Coords>
     */
    auto initializeCoordinates() -> std::deque<Coords>;

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
    auto colorGameButtons(sf::RenderWindow &window) -> void;

    /**
    * Function which simply checks whether game is ended or not.
    * @return bool
    */
    auto isEnd() -> bool;

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
    auto makeMove(int y, int x) -> void;

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
    auto counter(int ch) -> string;

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
    static auto readFile() -> string;

    /**
    * Function for coloring buttons their default colorChange.
    * @param colorChange
    * @return void
    */
    auto disableColor(const sf::Color &colorChange) -> pair<int, int>;

    /**
     * Function for getting all valid offsets to move.
     * @param y
     * @param x
     * @param range
     * @return
     */
    auto getValidPositions(int y, int x, int range) -> vector<pair<int, int>>;

    /**
     * Function for finding cell by q, r, s parameters represented as a vector.
     * @param coordinates
     * @return
     */
    auto find(vector<int> coordinates) -> pair<int, int>;

    /**
     * Function for defining possibility to move on particular cell.
     * @param y1
     * @param x1
     * @param y2
     * @param x2
     * @return
     */
    auto canMove(int y1, int x1, int y2, int x2) -> int;

    /**
     * Functions for finding offsets with enemies.
     * @param selected
     * @return
     */
    auto findEnemies(pair<int, int> selected) -> vector<pair<int, int>>;

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
    static auto loadGame(const string &path) -> Game;

    /**
    * Auxiliary function defined for fast buttons loading from the "savings" folder.
    * @param font
    * @return
    */
    static auto loadGameBut(const sf::Font &font) -> vector<unique_ptr<Button>>;

private:
    vector<vector<int>> mapInt = {{3},
                                  {1, 1},
                                  {1, 2, 1},
                                  {1, 1, 1, 1},
                                  {1, 1, 1, 1, 1},
                                  {1, 1, 1, 1},
                                  {1, 1, 1, 1, 1},
                                  {1, 1, 2, 1},
                                  {1, 1, 1, 1, 1},
                                  {1, 3, 1, 1},
                                  {1, 1, 1, 1, 1},
                                  {1, 1, 1, 1},
                                  {1, 1, 1, 1, 1},
                                  {1, 1, 1, 1},
                                  {1, 3, 1},
                                  {1, 1},
                                  {2}
    };

    sf::Time timer = sf::seconds(0);
    bool mode{};
    bool turn{};
    vector<vector<unique_ptr<Hex>>> mapHex;
};