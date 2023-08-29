#include "button.h"
#include "game.h"

enum class GameState {
    inMainMenu,
    inGame,
    inMode,
    inHighScores
};

auto main() -> int {
    GameState currentState = GameState::inMainMenu;

    auto window = sf::RenderWindow(sf::VideoMode(1200, 800), "Hexxagon");
    auto font = sf::Font{};
    auto icon = sf::Image{};
    auto clock = sf::Clock{};
    auto timer = sf::seconds(0);
    auto first = true;
    auto timerText = sf::Text("", font, 20);
    auto score = sf::Text("", font);

    score.setPosition(450, 250);

    icon.loadFromFile("icon.jpg");
    font.loadFromFile("CALISTB.ttf");

    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    timerText.setPosition(1090, 510);
    timerText.setFillColor(sf::Color::White);

    auto newGame = Button("New Game", {125, 65}, 20, sf::Color(128, 128, 128));
    auto highScores = Button("High Scores", {125, 65}, 20, sf::Color(128, 128, 128));
    auto exit = Button("Exit", {125, 65}, 20, sf::Color(128, 128, 128));
    auto computerVsPlayer = Button("Computer vs Player", {225, 65}, 20, sf::Color(128, 128, 128));
    auto playerVsPlayer = Button("Player vs Player", {225, 65}, 20, sf::Color(128, 128, 128));
    auto player1 = Button("0", {50, 50}, 20, sf::Color::Blue);
    auto player2 = Button("0", {50, 50}, 20, sf::Color::Cyan);
    auto gameOver = Button("Game over!", {200, 100}, 17, sf::Color(128, 128, 128));

    newGame.initializeBut({300, 300}, font, 10, 3);
    highScores.initializeBut({600, 300}, font, 10, 3);
    exit.initializeBut({900, 300}, font, 3, 3);
    playerVsPlayer.initializeBut({300, 300}, font, 6, 3);
    computerVsPlayer.initializeBut({750, 300}, font, 10, 3);
    player1.initializeBut({1100, 550}, font, 3, 4);
    player2.initializeBut({1100, 600}, font, 3, 4);
    player1.getText().setFillColor(sf::Color::Black);
    player2.getText().setFillColor(sf::Color::Black);
    gameOver.initializeBut({500, 300}, font, 5, 10);
    gameOver.getText().setFillColor(sf::Color::White);

    auto backgroundIm = sf::Texture{};
    backgroundIm.loadFromFile("backgroundMenu.jpg");
    auto background = sf::Sprite(backgroundIm);

    auto game = Game(true);

    while (window.isOpen()) {
        auto event = sf::Event{};
        while (window.pollEvent(event))
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
                    else if (computerVsPlayer.isMouseOver(window) && currentState == GameState::inMode)
                        currentState = GameState::inGame;
                    else if (playerVsPlayer.isMouseOver(window) && currentState == GameState::inMode) {
                        currentState = GameState::inGame;
                        game = Game(false);
                    } else if (currentState == GameState::inGame)
                        game.makeMove(window);
                    break;
                case sf::Event::KeyPressed:
                    if ((currentState == GameState::inGame || currentState == GameState::inMode ||
                         currentState == GameState::inHighScores) &&
                        event.key.code == sf::Keyboard::Escape) {
                        if (currentState == GameState::inGame)
                            Game::saveInFile(stoi(game.counter(1)), stoi(game.counter(2)));
                        currentState = GameState::inMainMenu;
                        first = true;
                    }
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
                window.draw(background);
                score.setString(Game::readFile());
                window.draw(score);
                break;
            case GameState::inGame:
                if (first) {
                    game.initializeMap(window, font);
                    first = false;
                    timer = sf::seconds(0);
                    clock.restart();
                } else if (game.checkEnd()/*true*/) {
                    auto result = std::stringstream();
                    result << "    Game over!\n     Player 1: " << game.counter(1) << "\n     Player 2: "
                           << game.counter(2)
                           << "\npress \"Esc\" to exit";
                    gameOver.getText().setString(result.str());
                    window.draw(background);
                    gameOver.drawBut(window);
                } else {
                    game.drawMap(window);
                    window.draw(timerText);
                    player1.drawBut(window);
                    player2.drawBut(window);

                    sf::Time elapsedTime = clock.restart();
                    timer += elapsedTime;
                    timerText.setString(std::to_string(timer.asSeconds()));

                    player1.getText().setString(game.counter(1));
                    player2.getText().setString(game.counter(2));
                }
                break;
        }

        window.display();
    }
    return 0;
}