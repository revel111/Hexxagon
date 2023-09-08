#include "button.h"
#include "game.h"
#include "gamestate.h"

auto main() -> int {
    auto currentState = GameState::inMainMenu;

    auto game = Game(true);

    auto window = sf::RenderWindow(sf::VideoMode(1200, 800), "Hexxagon");
    auto font = sf::Font{};
    auto icon = sf::Image{};
    auto clock = sf::Clock{};
    auto first = true;
    auto timerText = sf::Text("", font, 20);
    auto score = sf::Text("", font);
    auto loadGameText = sf::Text("Load Game", font, 25);
    auto saveGameText = sf::Text("Choose slot to overwrite", font, 23);
    auto deleteGameText = sf::Text("Choose slot to delete", font, 25);

    loadGameText.setPosition(550, 100);
    saveGameText.setPosition(485, 100);
    deleteGameText.setPosition(500, 100);

    timerText.setPosition(1090, 510);
    timerText.setFillColor(sf::Color::White);
    score.setPosition(450, 250);

    icon.loadFromFile("icon.jpg");
    font.loadFromFile("CALISTB.ttf");

    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    auto newGame = Button("New Game", {125, 65}, 20, sf::Color(128, 128, 128), {300, 300}, font, 10, 3);
    auto loadGame = Button("Load Game", {125, 65}, 20, sf::Color(128, 128, 128), {500, 300}, font, 10, 3);
    auto highScores = Button("High Scores", {125, 65}, 20, sf::Color(128, 128, 128), {700, 300}, font, 10, 3);
    auto exit = Button("Exit", {125, 65}, 20, sf::Color(128, 128, 128), {900, 300}, font, 3, 3);
    auto computerVsPlayer = Button("Computer vs Player", {225, 65}, 20, sf::Color(128, 128, 128), {750, 300}, font, 10,
                                   3);
    auto playerVsPlayer = Button("Player vs Player", {225, 65}, 20, sf::Color(128, 128, 128), {300, 300}, font, 6, 3);
    auto player1 = Button("0", {50, 50}, 20, sf::Color::Blue, {1100, 550}, font, 3, 4);
    auto player2 = Button("0", {50, 50}, 20, sf::Color::Cyan, {1100, 600}, font, 3, 4);
    auto gameOver = Button("Game over!", {200, 100}, 17, sf::Color(128, 128, 128), {500, 300}, font, 5, 10);
    auto saveGame = Button("Save Game", {100, 50}, 17, sf::Color(128, 128, 128), {1075, 700}, font, 10, 3);
    auto deleteGame = Button("Delete Game", {125, 50}, 17, sf::Color(128, 128, 128), {1000, 700}, font, 10, 3);

    auto loadVector = Game::loadGameBut(font);

    auto backgroundIm = sf::Texture{};
    backgroundIm.loadFromFile("backgroundMenu.jpg");
    auto background = sf::Sprite(backgroundIm);

    while (window.isOpen()) {
        auto event = sf::Event{};
        while (window.pollEvent(event))
            switch (event.type) {
                case sf::Event::MouseMoved:
                    switch (currentState) {
                        case GameState::inMainMenu:
                            newGame.colorButMenu(window);
                            loadGame.colorButMenu(window);
                            highScores.colorButMenu(window);
                            exit.colorButMenu(window);
                            break;
                        case GameState::inLoadGame:
                            deleteGame.colorButMenu(window);
                        case GameState::inDeleteGame:
                        case GameState::inSaveGame:
                            for (const auto &i: loadVector)
                                i->colorButMenu(window);
                            break;
                        case GameState::inMode:
                            computerVsPlayer.colorButMenu(window);
                            playerVsPlayer.colorButMenu(window);
                            break;
                        case GameState::inGame:
                            saveGame.colorButMenu(window);
                            break;
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (newGame.isMouseOver(window) && currentState == GameState::inMainMenu)
                        currentState = GameState::inMode;
                    else if (loadGame.isMouseOver(window) && currentState == GameState::inMainMenu) {
                        loadVector = Game::loadGameBut(font);
                        currentState = GameState::inLoadGame;
                    } else if (currentState == GameState::inLoadGame) {
                        for (const auto &i: loadVector)
                            if (i->isMouseOver(window) && i->getText().getString() != "Empty") {
                                game = Game::loadGame(i->getText().getString());
                                game.initializeMap(window, font);
                                currentState = GameState::inGame;
//                                first = false;
                            }
                        if (deleteGame.isMouseOver(window))
                            currentState = GameState::inDeleteGame;
                    } else if (currentState == GameState::inSaveGame || currentState == GameState::inDeleteGame) {
                        for (const auto &i: loadVector)
                            if (i->isMouseOver(window) && i->getText().getString() != "Empty") {
                                auto result = std::stringstream();
                                std::string str = i->getText().getString();
                                result << "savings/" << str;
                                auto file = std::filesystem::path(result.str());
                                std::filesystem::remove(file);
//                                first = true;
                            }
                        if (currentState == GameState::inSaveGame)
                            game.saveGame();
                        currentState = GameState::inMainMenu;
                    } else if (exit.isMouseOver(window) && currentState == GameState::inMainMenu)
                        window.close();
                    else if (highScores.isMouseOver(window) && currentState == GameState::inMainMenu)
                        currentState = GameState::inHighScores;
                    else if (computerVsPlayer.isMouseOver(window) && currentState == GameState::inMode) {
                        currentState = GameState::inGame;
                        first = true;
                    } else if (playerVsPlayer.isMouseOver(window) && currentState == GameState::inMode) {
                        currentState = GameState::inGame;
                        game = Game(false);
                        first = true;
                    } else if (saveGame.isMouseOver(window) && currentState == GameState::inGame)
                        currentState = GameState::inSaveGame;
                    else if (currentState == GameState::inGame) {
                        game.makeMove(window);
                    }
                    break;
                case sf::Event::KeyPressed:
                    if ((currentState == GameState::inGame || currentState == GameState::inMode ||
                         currentState == GameState::inHighScores || currentState == GameState::inLoadGame ||
                         currentState == GameState::inSaveGame || currentState == GameState::inDeleteGame) &&
                        event.key.code == sf::Keyboard::Escape) {
                        if (currentState == GameState::inGame)
                            Game::saveInFile(stoi(game.counter(1)), stoi(game.counter(2)));
                        currentState = GameState::inMainMenu;
//                        first = true;
                    }
            }

        window.clear();

        switch (currentState) {
            case GameState::inMainMenu:
                window.draw(background);
                newGame.drawBut(window);
                loadGame.drawBut(window);
                highScores.drawBut(window);
                exit.drawBut(window);
                break;
            case GameState::inLoadGame:
                window.draw(background);
                window.draw(loadGameText);
                deleteGame.drawBut(window);
                for (const auto &i: loadVector)
                    i->drawBut(window);
                break;
            case GameState::inSaveGame:
                window.draw(background);
                window.draw(saveGameText);
                for (const auto &i: loadVector)
                    i->drawBut(window);
                break;
            case GameState::inDeleteGame:
                window.draw(background);
                window.draw(deleteGameText);
                for (const auto &i: loadVector)
                    i->drawBut(window);
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
                    game.getTimer() = sf::seconds(0);
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
                    saveGame.drawBut(window);

                    auto elapsedTime = clock.restart();
                    game.getTimer() += elapsedTime;
                    timerText.setString(std::to_string(game.getTimer().asSeconds()));

                    player1.getText().setString(game.counter(1));
                    player2.getText().setString(game.counter(2));
                }
                break;
        }

        window.display();
    }
    return 0;
}