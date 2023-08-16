#include "butMenu.h"
#include "map.h"

enum class GameState {
    inMainMenu,
    inGame,
    inMode,
    inHighScores
};

int main() {
    GameState currentState = GameState::inMainMenu;

    auto window = sf::RenderWindow(sf::VideoMode(1200, 800), "Hexxagon");
    auto font = sf::Font{};
    auto icon = sf::Image{};
    auto mode = true;
    auto first = true;

    icon.loadFromFile("icon.jpg");
    font.loadFromFile("CALISTB.ttf");

    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    auto newGame = ButtonMenu("New Game", {125, 65}, 20, sf::Color(128, 128, 128));
    auto highScores = ButtonMenu("High Scores", {125, 65}, 20, sf::Color(128, 128, 128));
    auto exit = ButtonMenu("Exit", {125, 65}, 20, sf::Color(128, 128, 128));
    auto computerVsPlayer = ButtonMenu("Computer vs Player", {225, 65}, 20, sf::Color(128, 128, 128));
    auto playerVsPlayer = ButtonMenu("Player vs Player", {225, 65}, 20, sf::Color(128, 128, 128));

    newGame.initializeBut({300, 300}, font);
    highScores.initializeBut({600, 300}, font);
    exit.initializeBut({900, 300}, font);
    computerVsPlayer.initializeBut({300, 300}, font);
    playerVsPlayer.initializeBut({750, 300}, font);

    auto backgroundIm = sf::Texture{};
    backgroundIm.loadFromFile("backgroundMenu.jpg");
    auto background = sf::Sprite(backgroundIm);

    auto map = Map();

    while (window.isOpen()) {
        auto event = sf::Event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::MouseMoved:
                    switch (currentState) {
                        case GameState::inMainMenu:
                            newGame.colorButMenu(window);
                            highScores.colorButMenu(window);
                            exit.colorButMenu(window);
                            break;
                        case GameState::inMode:
                            computerVsPlayer.colorButMenu(window);
                            playerVsPlayer.colorButMenu(window);
                            break;
                        case GameState::inGame:

                            break;
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (newGame.isMouseOver(window) && currentState == GameState::inMainMenu)
                        currentState = GameState::inMode;
                    else if (exit.isMouseOver(window) && currentState == GameState::inMainMenu)
                        window.close();
                    else if (highScores.isMouseOver(window) && currentState == GameState::inMainMenu)
                        currentState = GameState::inHighScores;
                    else if (computerVsPlayer.isMouseOver(window) && currentState == GameState::inMode) {
                        currentState = GameState::inGame;
                        map = Map();
                    } else if (playerVsPlayer.isMouseOver(window) && currentState == GameState::inMode) {
                        currentState = GameState::inGame;
                        mode = false;
                    } else if (currentState == GameState::inGame)
                        map.makeMove(window);
                    break;
            }
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
//                if (currentState == GameState::inMainMenu)
//                    currentState = GameState::inGame;
//                else
//                    currentState = GameState::inMainMenu;
        }

        window.clear();

        switch (currentState) {
            case GameState::inMainMenu:
                window.draw(background);
                newGame.drawBut(window);
                highScores.drawBut(window);
                exit.drawBut(window);
                break;
            case GameState::inMode:
                window.draw(background);
                playerVsPlayer.drawBut(window);
                computerVsPlayer.drawBut(window);
                break;
            case GameState::inHighScores:

                break;
            case GameState::inGame:
                if (first) {
                    map.initializeMap(window, font);
                    first = false;
                } else
                    map.drawMap(window);
                break;
        }

        window.display();
    }
    return 0;
}