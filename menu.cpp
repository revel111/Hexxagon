#include "menu.h"

Menu::Menu(int width, int height) : window(sf::VideoMode(width, height), "Hexxagon") {
    loader();
    initializeButtons();
    initializeText();
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    loadVector = Game::loadGameBut(font);
}

auto Menu::render() -> void {
    while (window.isOpen()) {
        auto event = sf::Event{};

        while (window.pollEvent(event))
            renderEvent(event);

        window.clear();

        renderState();

        window.display();
    }
}

auto Menu::renderEvent(sf::Event event) -> void {
    switch (event.type) {
        /** Color menu buttons when mouse moves.*/
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
                case GameState::inHighScores:
                    break;
            }
            break;
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            switch (currentState) {
                case GameState::inMainMenu:
                    if (newGame.isMouseOver(window))
                        currentState = GameState::inMode;
                    else if (loadGame.isMouseOver(window)) {
                        loadVector = Game::loadGameBut(font);
                        currentState = GameState::inLoadGame;
                    } else if (exit.isMouseOver(window))
                        window.close();
                    else if (highScores.isMouseOver(window))
                        currentState = GameState::inHighScores;
                    break;
                case GameState::inGame:
                    if (saveGame.isMouseOver(window))
                        currentState = GameState::inSaveGame;
                    else
                        game.makeMove(window);
                    break;
                case GameState::inMode:
                    if (computerVsPlayer.isMouseOver(window)) {
                        currentState = GameState::inGame;
                        game = Game(true);
                        first = true;
                    } else if (playerVsPlayer.isMouseOver(window)) {
                        currentState = GameState::inGame;
                        game = Game(false);
                        first = true;
                    }
                    break;
                case GameState::inHighScores:
                    break;
                case GameState::inLoadGame:
                    for (const auto &i: loadVector)
                        if (i->isMouseOver(window) && i->getText().getString() != "Empty") {
                            game = Game::loadGame(i->getText().getString());
                            game.initializeMap(window, font);
                            currentState = GameState::inGame;
                            first = false;
                        }
                    if (deleteGame.isMouseOver(window))
                        currentState = GameState::inDeleteGame;
                    break;
                case GameState::inSaveGame:
                case GameState::inDeleteGame:
                    for (const auto &i: loadVector)
                        if (i->isMouseOver(window) && i->getText().getString() != "Empty") {
                            auto result = std::stringstream();
                            std::string str = i->getText().getString();
                            result << "savings/" << str;
                            auto file = std::filesystem::path(result.str());
                            std::filesystem::remove(file);
                        }
                    if (currentState == GameState::inSaveGame)
                        game.saveGame();

                    currentState = GameState::inMainMenu;
                    break;
            }
            break;
        case sf::Event::KeyPressed:
            if (currentState != GameState::inMainMenu && event.key.code == sf::Keyboard::Escape) {
                if (currentState == GameState::inGame)
                    Game::saveInFile(stoi(game.counter(1)), stoi(game.counter(2)));

                currentState = GameState::inMainMenu;
            }
    }
}

auto Menu::renderState() -> void {
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
            scoreText.setString(Game::readFile());
            window.draw(scoreText);
            break;
        case GameState::inGame:
            if (first) {
                game.initializeMap(window, font);
                first = false;
                game.getTimer() = sf::seconds(0);
                clock.restart();
            } else if (game.checkEnd()) {
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
}

auto Menu::initializeButtons() -> void {
    newGame = Button("New Game", {125, 65}, 20, sf::Color(128, 128, 128), {300, 300}, font, 10, 3);
    loadGame = Button("Load Game", {125, 65}, 20, sf::Color(128, 128, 128), {500, 300}, font, 10, 3);
    highScores = Button("High Scores", {125, 65}, 20, sf::Color(128, 128, 128), {700, 300}, font, 10, 3);
    exit = Button("Exit", {125, 65}, 20, sf::Color(128, 128, 128), {900, 300}, font, 3, 3);
    computerVsPlayer = Button("Computer vs Player", {225, 65}, 20, sf::Color(128, 128, 128), {750, 300}, font, 10, 3);
    playerVsPlayer = Button("Player vs Player", {225, 65}, 20, sf::Color(128, 128, 128), {300, 300}, font, 6, 3);
    player1 = Button("0", {50, 50}, 20, sf::Color::Blue, {1100, 550}, font, 3, 4);
    player2 = Button("0", {50, 50}, 20, sf::Color::Cyan, {1100, 600}, font, 3, 4);
    gameOver = Button("Game over!", {200, 100}, 17, sf::Color(128, 128, 128), {500, 300}, font, 5, 10);
    saveGame = Button("Save Game", {100, 50}, 17, sf::Color(128, 128, 128), {1075, 700}, font, 10, 3);
    deleteGame = Button("Delete Game", {125, 50}, 17, sf::Color(128, 128, 128), {1000, 700}, font, 10, 3);
}

auto Menu::loader() -> void {
    icon.loadFromFile("icon.jpg");
    font.loadFromFile("CALISTB.ttf");

    backgroundIm = sf::Texture{};
    backgroundIm.loadFromFile("backgroundMenu.jpg");
    background = sf::Sprite(backgroundIm);
}

auto Menu::initializeText() -> void {
    timerText = sf::Text("", font, 20);
    scoreText = sf::Text("", font);
    loadGameText = sf::Text("Load Game", font, 25);
    saveGameText = sf::Text("Choose slot to overwrite", font, 23);
    deleteGameText = sf::Text("Choose slot to delete", font, 25);

    loadGameText.setPosition(550, 100);
    saveGameText.setPosition(485, 100);
    deleteGameText.setPosition(500, 100);
    scoreText.setPosition(450, 250);
    timerText.setPosition(1090, 510);
    timerText.setFillColor(sf::Color::White);
}

