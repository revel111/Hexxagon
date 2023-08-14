#include "buttonFuncs.h"

enum class GameState {
    inMainMenu,
    inGame,
    inHighScores
};

int main() {
    GameState currentState = GameState::inMainMenu;

    auto window = sf::RenderWindow(sf::VideoMode(1200, 800), "Hexxagon");
    auto font = sf::Font{};
    auto icon = sf::Image{};

    icon.loadFromFile("icon.jpg");
    font.loadFromFile("CALISTB.ttf");

    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    auto newGame = Button("New Game");
    auto highScores = Button("High Scores");
    auto exit = Button("Exit");
//    const std::initializer_list<Button> &buttons = {newGame,highScores, newGame};
    Button::initializeBut(newGame, {300, 300}, font);
    Button::initializeBut(highScores, {600, 300}, font);
    Button::initializeBut(exit, {900, 300}, font);

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
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (newGame.isMouseOver(window))
                        currentState = GameState::inGame;
                    else if (exit.isMouseOver(window))
                        window.close();
                    else if (newGame.isMouseOver(window))
                        currentState = GameState::inHighScores;
                    break;
            }
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
//                if (currentState == GameState::inMainMenu)
//                    currentState = GameState::inGame;
//                else
//                    currentState = GameState::inMainMenu;
        }

        window.clear();

        window.draw(background);

        if (currentState == GameState::inMainMenu) {
            newGame.drawBut(window);
            highScores.drawBut(window);
            exit.drawBut(window);
        } else {
            exit.drawBut(window);
        }

        window.display();
    }
    return 0;
}