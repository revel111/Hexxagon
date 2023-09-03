#include "game.h"

Game::Game(bool mode) {
    this->mode = mode;
    turn = false;
}

Game::Game(const std::vector<std::vector<int>> &mapInt, bool mode, bool turn, const sf::Time &timer) {
    this->mapInt = mapInt;
    this->mode = mode;
    this->turn = turn;
    this->timer = timer;
}

sf::Time &Game::getTimer() {
    return timer;
}

auto Game::initializeMap(sf::RenderWindow &window, const sf::Font &font) -> void {
    mapBut.resize(mapInt.size());
    auto maxColumns = 0;

    for (const auto &row: mapInt)
        if (row.size() > maxColumns)
            maxColumns = row.size();

    auto startX = (1200 - (50 * 1.5f) * maxColumns) / 2;
    auto startY = (800 - (std::sqrt(3.0f) * 25) * (mapInt.size() + 0.5)) / 2;

    for (auto i = 0; i < mapInt.size(); i++) {
        auto currentStartX = startX;
        switch (mapInt[i].size()) {
            case 1:
                currentStartX += 150;
                break;
            case 2:
                currentStartX += 110;
                break;
            case 3:
                currentStartX += 75;
                break;
            case 4:
                currentStartX += 35;
                break;
        }

        for (auto j = 0; j < mapInt[i].size(); j++) {
            auto pos = sf::Vector2f{currentStartX + j * (50 * 1.5f),
                                    static_cast<float>(startY + i * (std::sqrt(3.0f) * 25) + 1)};
            auto button = std::make_unique<Button>("", sf::Vector2f(30, 30), 15, sf::Color::Black, pos, font, 4, 4);
            switch (mapInt[i][j]) {
                case 0:
                    button->getText().setString("X");
                    button->getText().setFillColor(sf::Color(128, 128, 128));
                    button->setDefColor(sf::Color(128, 128, 128));
                    break;
                case 1:
                    button->getText().setString("O");
                    button->setDefColor(sf::Color::White);
                    break;
                case 2:
                    button->getText().setString("1");
                    button->getText().setFillColor(sf::Color::Blue);
                    button->setDefColor(sf::Color::Blue);
                    break;
                case 3:
                    button->getText().setString("2");
                    button->getText().setFillColor(sf::Color::Cyan);
                    button->setDefColor(sf::Color::Cyan);
                    break;
            }
            mapBut[i].push_back(std::move(button));
            mapBut[i][j]->drawBut(window);
        }
    }
}

auto Game::drawMap(sf::RenderWindow &window) -> void {
    for (auto &i: mapBut)
        for (const auto &j: i)
            j->drawBut(window);
}

auto Game::makeMove(sf::RenderWindow &window) -> void {
    for (auto i = 0; i < mapBut.size(); i++)
        for (auto j = 0; j < mapBut[i].size(); j++)
            colorButGame(window, i, j);
}

auto Game::checkEnd() -> bool {
    /*auto totalCounter = 0;
    for (auto i = 0; i < mapBut.size(); i++)
        for (auto j = 0; j < mapBut[i].size(); j++)
            if (mapBut[i][j]->getText().getString() == "O")
                return false;
            else if (mapBut[i][j]->getText().getString() == "1" || mapBut[i][j]->getText().getString() == "2") {
                auto offsetCounter = 0;
                for (const auto &offset: offsetEnemy) {
                    auto newY = i + offset[0];
                    auto newX = j + offset[1];

                    if (mapBut[newY].size() == 5) {
                        if ((offset[0] == 1 && offset[1] == -1) ||
                            (offset[0] == -1 && offset[1] == -1)) {
                            offsetCounter++;
                            continue;
                        }
                    } else if (mapBut[newY].size() == 4)
                        if ((offset[0] == -1 && offset[1] == 1) ||
                            (offset[0] == 1 && offset[1] == 1)) {
                            offsetCounter++;
                            continue;
                        }

                    if (newX >= 0 && newY < mapBut.size() && newY >= 0 && newX < mapBut[newY].size()) {
                        if (mapBut[newY][newX]->getText().getString() == "2" ||
                            mapBut[newY][newX]->getText().getString() == "1") {
                            offsetCounter++;
                        }
                    } else
                        totalCounter++;

                }
                if (offsetCounter == offsetEnemy.size())
                    totalCounter++;
                else
                    return false;
            }*/

    if (/*totalCounter == mapBut.size() ||*/ counter(1) == "0" || counter(2) == "0" || counter(3) == "0")
        return true;
    return false;
}

auto Game::checkSelected() -> bool {
    for (auto &i: mapBut)
        for (const auto &j: i)
            if (j->getText().getFillColor() == sf::Color::Green)
                return true;

    return false;
}

auto Game::colorButGame(sf::RenderWindow &window, int y, int x) -> void {
    if (!mode || (mode && !turn)) {
        if (mapBut[y][x]->isMouseOver(window) && checkSelected())
            if (mapBut[y][x]->getText().getFillColor() == sf::Color::Green) {
                mapBut[y][x]->getText().setFillColor(mapBut[y][x]->getDefColor());
                disableColor(false);
            } else
                checkMove(y, x);
        else if (mapBut[y][x]->isMouseOver(window))
            if ((turn && mapBut[y][x]->getText().getString() == "2") ||
                (!turn && mapBut[y][x]->getText().getString() == "1")) {
                mapBut[y][x]->getText().setFillColor(sf::Color::Green);
                disableColor(true);
                colorPossible(/*y, x*/);
            }
    } else if (mode && turn) {
        aiMakeMove();
        turn = !turn;
    }
}

auto Game::checkMove(int y, int x) -> void {
    auto selectedX = 0, selectedY = 0;
//    auto selected = findSelected();

//    mapBut[selected.at(0)][selected.at(1)]->getText().setFillColor(
//            mapBut[selected.at(0)][selected.at(1)]->getDefColor());

    for (auto i = 0; i < mapBut.size(); i++)
        for (auto j = 0; j < mapBut[i].size(); j++)
            if (mapBut[i][j]->getText().getFillColor() == sf::Color::Green) {
                selectedX = j, selectedY = i;
                mapBut[selectedY][selectedX]->getText().setFillColor(mapBut[selectedY][selectedX]->getDefColor());
            }

//    if (abs(selected.at(1) - x) <= 2 && abs(selected.at(0) - y) <= 4 &&
//        ((selected.at(1) + selected.at(0)) - (x + y)) <= 2 &&
//        mapBut[y][x]->getText().getString() == "O") {
//        if ((abs(selected.at(1) - x) == 2) || ((abs(selected.at(0) - y)) == 4) || ((abs(selected.at(0) - y)) == 3)) {
//            mapBut[selected.at(0)][selected.at(1)]->getText().setString("O");
//            mapBut[selected.at(0)][selected.at(1)]->setDefColor(sf::Color::White);
//            mapBut[selected.at(0)][selected.at(1)]->getText().setFillColor(sf::Color::White);
//        }

    if (abs(selectedX - x) <= 2 && abs(selectedY - y) <= 4 &&
        ((selectedX + selectedY) - (x + y)) <= 2 &&
        mapBut[y][x]->getText().getString() == "O") {
        if ((abs(selectedX - x) == 2) || ((abs(selectedY - y)) == 4) || ((abs(selectedY - y)) == 3)) {
            mapBut[selectedY][selectedX]->getText().setString("O");
            mapBut[selectedY][selectedX]->setDefColor(sf::Color::White);
            mapBut[selectedY][selectedX]->getText().setFillColor(sf::Color::White);
        }

        for (const auto &offset: offsetEnemy) {
            auto newY = y + offset[0];
            auto newX = x + offset[1];

//            if (mapBut[newY].size() == 5) {
//                if ((offset[0] == 1 && offset[1] == -1) ||
//                    (offset[0] == -1 && offset[1] == -1)) {
//                    continue;
//                }
//            } else if (mapBut[newY].size() <= 4)
//                if ((offset[0] == -1 && offset[1] == 1) ||
//                    (offset[0] == 1 && offset[1] == 1)) {
//                    continue;
//                }
//
//
//            auto biggest = std::max(mapBut[newY].size(), mapBut[y].size());
//            auto smallest = std::min(mapBut[newY].size(), mapBut[y].size());
//            std::cout << smallest << " " << biggest << std::endl;
//
//            if (newX >= mapBut[newY].size()) {
//                newX = mapBut[newY].size() - 1;
//            }

            if (newX >= 0 && newY < mapBut.size() && newY >= 0 && newX < mapBut[newY].size()) {
                if (mapBut[newY][newX]->getText().getString() == "2" && !turn) {
                    mapBut[newY][newX]->getText().setString("1");
                    mapBut[newY][newX]->setDefColor(sf::Color::Blue);
                    mapBut[newY][newX]->getText().setFillColor(sf::Color::Blue);
                } else if (mapBut[newY][newX]->getText().getString() == "1" && turn) {
                    mapBut[newY][newX]->getText().setString("2");
                    mapBut[newY][newX]->setDefColor(sf::Color::Cyan);
                    mapBut[newY][newX]->getText().setFillColor(sf::Color::Cyan);
                }
            }
        }

        if (turn) {
            mapBut[y][x]->getText().setString("2");
            mapBut[y][x]->getText().setFillColor(sf::Color::Cyan);
            mapBut[y][x]->setDefColor(sf::Color::Cyan);
        } else {
            mapBut[y][x]->getText().setString("1");
            mapBut[y][x]->getText().setFillColor(sf::Color::Blue);
            mapBut[y][x]->setDefColor(sf::Color::Blue);
        }
        turn = !turn;
        disableColor(false);
    } else {
        mapBut[y][x]->getText().setFillColor(sf::Color::Red);
        disableColor(false);
    }
}

auto Game::colorPossible(/*int y, int x*/) -> void {
//    auto selected = findSelected();
//    auto selectedX = 0, selectedY = 0;
//
//    for (auto i = 0; i < mapBut.size(); i++)
//        for (auto j = 0; j < mapBut[i].size(); j++)
//            if (mapBut[i][j]->getText().getFillColor() == sf::Color::Green) {
//                selectedX = j, selectedY = i;
//                mapBut[selectedY][selectedX]->getText().setFillColor(mapBut[selectedY][selectedX]->getDefColor());
//            }
//
//    for (auto x = 0; x < mapBut.size(); x++)
//        for (auto y = 0; y < mapBut[x].size(); y++)
//            if (abs(selectedX - x) <= 2 && abs(selectedY - y) <= 4 &&
//                ((selectedX + selectedY) - (x + y)) <= 2 &&
//                mapBut[y][x]->getText().getString() == "O") {
//                mapBut[y][x]->getText().setFillColor(sf::Color::Yellow);
//            }
}

auto Game::counter(int ch) -> std::string {
    auto count = 0;
    for (auto &i: mapBut)
        for (const auto &j: i)
            if ((j->getText().getString() == "1" && ch == 1) || (j->getText().getString() == "2" && ch == 2) ||
                (j->getText().getString() == "O" && ch == 3))
                count++;

    return std::to_string(count);
}

auto Game::aiMakeMove() -> void {
    std::map<std::vector<int>, int> choices;
    for (auto i = 0; i < mapBut.size(); i++) {
        for (auto j = 0; j < mapBut[i].size(); j++) {
            if (mapBut[i][j]->getText().getString() == "2") {
                std::vector<int> newVector;
                newVector.insert(newVector.end(), {i, j});
                choices.insert({newVector, 0});

//                for (int k = 0; k < ; ++k) {
//
//                }

                for (const auto &offset: offsetEnemy) {
                    auto newY = i + offset[0];
                    auto newX = j + offset[1];

//            if (mapBut[newY].size() == 5) {
//                if ((offset[0] == 1 && offset[1] == -1) ||
//                    (offset[0] == -1 && offset[1] == -1)) {
//                    continue;
//                }
//            } else if (mapBut[newY].size() <= 4)
//                if ((offset[0] == -1 && offset[1] == 1) ||
//                    (offset[0] == 1 && offset[1] == 1)) {
//                    continue;
//                }
//
//
//            auto biggest = std::max(mapBut[newY].size(), mapBut[y].size());
//            auto smallest = std::min(mapBut[newY].size(), mapBut[y].size());
//            std::cout << smallest << " " << biggest << std::endl;
//
//            if (newX >= mapBut[newY].size()) {
//                newX = mapBut[newY].size() - 1;
//            }
                    if (newX >= 0 && newY < mapBut.size() && newY >= 0 && newX < mapBut[newY].size() &&
                        mapBut[newY][newX]->getText().getString() == "O")
                        choices.find(newVector)->second++;
                } //offset for walking
            }
        }
    }

    auto best = std::max_element(choices.begin(), choices.end(),
                                 [](std::pair<const std::vector<int>, int> a,
                                    std::pair<const std::vector<int>, int> b) -> bool {
                                     return a.second < b.second;
                                 });
//    checkMove(best->first.at(0), best->first.at(1));
}

auto Game::findSelected() -> std::vector<int> {
    auto newVector = std::vector<int>();
    for (auto i = 0; i < mapBut.size(); i++)
        for (auto j = 0; j < mapBut[i].size(); j++)
            if (mapBut[i][j]->getText().getFillColor() == sf::Color::Green)
                newVector.insert(newVector.end(), {i, j});

    return newVector;
}

auto Game::saveInFile(int player1, int player2) -> void {
    auto result = readFile();
    auto results = std::vector<std::vector<int>>();
    auto secondValue = true;
    auto putInFile = std::stringstream();
    auto file = std::ofstream("results.txt");

    auto pattern = std::regex(": (\\d+)");
    auto iss = std::istringstream(result);
    auto match = std::smatch();
    auto line = std::string();

    while (std::getline(iss, line))
        while (std::regex_search(line, match, pattern)) {
            int value = std::stoi(match[1].str());
            secondValue ? results.push_back({value}) : results.back().push_back(value);
            secondValue = !secondValue;
            line = match.suffix().str();
        }

    auto sortResults = [](const std::vector<int> &first, const std::vector<int> &second) -> bool {
        auto nonNullA = 0, nonNullB = 0;

        if (first[1] != 0)
            nonNullA = first[1];

        if (second[1] != 0)
            nonNullB = second[1];

        return abs(nonNullA - first[0]) > abs(nonNullB - second[0]);
    };

    results.push_back({player1});
    results.back().push_back(player2);

    std::sort(results.begin(), results.end(), sortResults);

    if (results.size() == 6)
        results.erase(results.begin() + results.size());

    for (auto &resultInFile: results)
        putInFile << "Player 1: " << resultInFile[0] << "; Player 2: " << resultInFile[1] << '\n';

    file << putInFile.str();

    file.close();
}

auto Game::readFile() -> std::string {
    auto file = std::ifstream("results.txt");
    auto result = std::string();
    auto line = std::string();

    while (getline(file, line))
        result += line + '\n';

    file.close();
    return result;
}

auto Game::disableColor(bool ch) -> void {
    for (auto &i: mapBut)
        for (const auto &j: i)
            if (j->getText().getFillColor() == sf::Color::Red && ch) {
                j->getText().setFillColor(j->getDefColor());
                break;
            } else if (j->getText().getFillColor() == sf::Color::Yellow && !ch)
                j->getText().setFillColor(j->getDefColor());
}

auto Game::saveGame() -> void {
    auto now = time(nullptr);
    auto putInFile = std::stringstream();
    char timeString[80];

    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H-%M-%S", localtime(&now));

    putInFile << "savings/" << timeString;

    auto file = std::ofstream(putInFile.str());

    for (auto &i: mapBut) {
        for (const auto &j: i)
            if (j->getText().getString() == 'X')
                file << "0 ";
            else if (j->getText().getString() == 'O')
                file << "1 ";
            else if (j->getText().getString() == '1')
                file << "2 ";
            else if (j->getText().getString() == '2')
                file << "3 ";
        file << '\n';
    }

    putInFile = std::stringstream();

    if (mode)
        putInFile << " Mode " << "1 ";
    else
        putInFile << " Mode " << "0 ";

    if (turn)
        putInFile << "Turn " << "1";
    else
        putInFile << "Turn " << "0";

    file << "Time " << timer.asSeconds() << putInFile.str();

    file.close();
}

auto Game::loadGame(const std::string &path) -> Game {
    auto putInFile = std::stringstream();
    putInFile << "savings/" << path;
    auto file = std::ifstream(putInFile.str());
    auto newMapInt = std::vector<std::vector<int>>();
    auto line = std::string();
    auto turnFrom = false;
    auto modeFrom = false;
    float varTime = 0.0;

    while (getline(file, line, '\n')) {
        auto tempVec = std::vector<int>();
        auto ss = std::istringstream(line);

        while (ss >> line) {
            if (line == "Time")
                ss >> varTime;
            else if (line == "Mode")
                ss >> modeFrom;
            else if (line == "Turn")
                ss >> turnFrom;
            else
                tempVec.push_back(stoi(line));
        }
        newMapInt.emplace_back(tempVec);
    }

    auto timeString = sf::seconds(varTime);

    file.close();

    return {newMapInt, modeFrom, turnFrom, timeString};
}

auto Game::loadGameBut(const sf::Font &font) -> std::vector<std::unique_ptr<Button>> {
    auto newVector = std::vector<std::unique_ptr<Button>>();
    auto pos = sf::Vector2f{500, 150};

    for (const auto &entry: std::filesystem::directory_iterator("savings")) {
        auto button = std::make_unique<Button>(entry.path().filename().string(), sf::Vector2f(225, 50), 20,
                                               sf::Color(128, 128, 128), pos, font, 10, 3);
        newVector.push_back(std::move(button));
        pos.y += 75;
    }

    while (newVector.size() < 7) {
        auto button = std::make_unique<Button>("Empty", sf::Vector2f(225, 50), 20,
                                               sf::Color(128, 128, 128), pos, font, 10, 3);
        newVector.push_back(std::move(button));
        pos.y += 75;
    }

    return newVector;
}