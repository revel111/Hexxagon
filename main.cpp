#include "buttonFuncs.h"
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

    icon.loadFromFile("icon.jpg");
    font.loadFromFile("CALISTB.ttf");

    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    auto newGame = Button("New Game", {125, 65}, 20, sf::Color(128, 128, 128));
    auto highScores = Button("High Scores", {125, 65}, 20, sf::Color(128, 128, 128));
    auto exit = Button("Exit", {125, 65}, 20, sf::Color(128, 128, 128));
    auto computerVsPlayer = Button("Computer vs Player", {225, 65}, 20, sf::Color(128, 128, 128));
    auto playerVsPlayer = Button("Player vs Player", {225, 65}, 20, sf::Color(128, 128, 128));
//    const std::initializer_list<Button> &buttons = {newGame,highScores, newGame};

    Button::initializeBut(newGame, {300, 300}, font);
    Button::initializeBut(highScores, {600, 300}, font);
    Button::initializeBut(exit, {900, 300}, font);
    Button::initializeBut(computerVsPlayer, {300, 300}, font);
    Button::initializeBut(playerVsPlayer, {750, 300}, font);

    auto backgroundIm = sf::Texture{};
    backgroundIm.loadFromFile("backgroundMenu.jpg");
    auto background = sf::Sprite(backgroundIm);

    while (window.isOpen()) {
        auto event = sf::Event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::MouseMoved:
                    Button::colorBut(newGame, window);
                    Button::colorBut(highScores, window);
                    Button::colorBut(exit, window);
                    Button::colorBut(computerVsPlayer, window);
                    Button::colorBut(playerVsPlayer, window);
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
                    else if (computerVsPlayer.isMouseOver(window) && currentState == GameState::inMode)
                        currentState = GameState::inGame;
                    else if (playerVsPlayer.isMouseOver(window) && currentState == GameState::inMode) {
                        currentState = GameState::inGame;
                        mode = false;
                    }
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
                Map::draw(window, font);
                break;
        }

        window.display();
    }
    return 0;
}