#pragma once

#include "gamestate.h"
#include "button.h"
#include "game.h"
#include <SFML/Graphics.hpp>
using std::unique_ptr, std::vector;

class Menu {
public:
    Menu(int width, int height);

    /**
     * Function for rendering window.
     */
    auto render() -> void;

    /**
     * Function for rendering events.
     */
    auto renderEvent(sf::Event event) -> void;

    auto renderState() -> void;

    auto initializeButtons() -> void;

    auto loader() -> void;

    auto initializeText() -> void;

private:
    GameState currentState = GameState::inMainMenu;
    sf::RenderWindow window;
    sf::Sprite background;
    sf::Texture backgroundIm;
    sf::Clock clock;
    Game game;
    //Buttons
    Button newGame;
    Button loadGame;
    Button highScores;
    Button exit;
    Button computerVsPlayer;
    Button playerVsPlayer;
    Button player1;
    Button player2;
    Button gameOver;
    Button saveGame;
    Button deleteGame;
    //To load
    sf::Font font;
    sf::Image icon;
    //Text
    sf::Text timerText;
    sf::Text scoreText;
    sf::Text loadGameText;
    sf::Text saveGameText;
    sf::Text deleteGameText;

    vector<unique_ptr<Button>> loadVector;
    bool first = true;
};