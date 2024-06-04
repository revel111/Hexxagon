#include "game.h"

Game::Game(bool mode) {
    this->mode = mode;
    turn = false;
}

Game::Game(const vector<vector<int>> &mapInt, bool mode, bool turn, const sf::Time &timer) {
    this->mapInt = mapInt;
    this->mode = mode;
    this->turn = turn;
    this->timer = timer;
}

Game::Game() = default;

auto Game::getTimer() -> sf::Time & {
    return timer;
}

auto Game::initializeMap(sf::RenderWindow &window, const sf::Font &font) -> void {
    mapBut.resize(mapInt.size());
    auto maxColumns = 0;

    for (const auto &row: mapInt)
        if (row.size() > maxColumns)
            maxColumns = row.size();

    auto buttonRadius = 30.0f;
    auto buttonSpacingX = buttonRadius * 1.75f;
    auto buttonSpacingY = buttonRadius * 1.48f;

    auto startX = (1200 - buttonSpacingX * maxColumns) / 2;
    auto startY = (800 - buttonSpacingY * (mapInt.size() + 0.5)) / 2;

    for (auto i = 0; i < mapInt.size(); i++) {
        auto currentStartX = startX + (buttonSpacingX / 2) * (maxColumns - mapInt[i].size());

        for (auto j = 0; j < mapInt[i].size(); j++) {
            auto pos = sf::Vector2f{currentStartX + j * buttonSpacingX, static_cast<float>(startY + i * buttonSpacingY)};
            auto button = std::make_unique<Button>("", buttonRadius, 10, sf::Color::Black, pos, font, 6);

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
    if (counter(1) == "0" || counter(2) == "0" || counter(3) == "0")
        return true;

    for (auto y = 0; y < mapBut.size(); y++)
        for (auto x = 0; x < mapBut[y].size(); x++)
            if (mapBut[y][x]->getText().getString() == "1" || mapBut[y][x]->getText().getString() == "2")
                for (const auto &offset: offsetEnemy) {
                    auto newY = y + offset[0];
                    auto newX = x + offset[1];

                    if (newX >= 0 && newY < mapBut.size() && newY >= 0 && newX < mapBut[newY].size()) {
                        if (mapBut[newY][newX]->getText().getString() == "O")
                            return false;
                    }
                }

    return true;
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
        if (mapBut[y]
            [x]->isMouseOver(window) && checkSelected())
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
                colorPossible(y, x);
            }
    } else if (mode && turn)
        aiMakeMove();
}

auto Game::checkMove(int y, int x) -> void {
    auto selectedX = 0, selectedY = 0;

    for (auto i = 0; i < mapBut.size(); i++)
        for (auto j = 0; j < mapBut[i].size(); j++)
            if (mapBut[i][j]->getText().getFillColor() == sf::Color::Green) {
                selectedX = j, selectedY = i;
                mapBut[selectedY][selectedX]->getText().setFillColor(mapBut[selectedY][selectedX]->getDefColor());
            }

    if (abs(selectedX - x) <= 2 && abs(selectedY - y) <= 4 && mapBut[y][x]->getText().getString() == "O") {
        if ((abs(selectedX - x) == 2) || ((abs(selectedY - y)) == 4) || ((abs(selectedY - y)) == 3)) {
            mapBut[selectedY][selectedX]->getText().setString("O");
            mapBut[selectedY][selectedX]->setDefColor(sf::Color::White);
            mapBut[selectedY][selectedX]->getText().setFillColor(sf::Color::White);
        }

        for (const auto &offset: offsetEnemy) {
            auto newY = y + offset[0];
            auto newX = x + offset[1];

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
    } else
        mapBut[y][x]->getText().setFillColor(sf::Color::Red);

    disableColor(false);
}

auto Game::colorPossible(int y, int x) -> void {
    for (auto i = 0; i < mapBut.size(); i++)
        for (auto j = 0; j < mapBut[i].size(); j++)
            if (abs(x - j) <= 2 && abs(y - i) <= 4 && mapBut[i][j]->getText().getString() == "O")
                mapBut[i][j]->getText().setFillColor(sf::Color::Yellow);
}

auto Game::counter(int ch) -> string {
    auto count = 0;

    for (auto &i: mapBut)
        for (const auto &j: i) {
            string content = j->getText().getString();

            if ((content == "1" && ch == 1) || (content == "2" && ch == 2) || (content == "O" && ch == 3))
                count++;
        }

    return std::to_string(count);
}

auto Game::aiMakeMove() -> void {
    auto choices = std::map<pair<pair<int, int>, pair<int, int>>, int>();
    auto selected = pair<int, int>();
    auto available = pair<int, int>();
    auto counter = 0;

    for (auto selectedY = 0; selectedY < mapBut.size(); selectedY++)  // for searching friend pawns
        for (auto selectedX = 0; selectedX < mapBut[selectedY].size(); selectedX++) {
            if (mapBut[selectedY][selectedX]->getText().getString() == "2") {
                selected = pair<int, int>(selectedY, selectedX);

                for (auto availableY = 0; availableY < mapBut.size(); availableY++) // for searching available
                    for (auto availableX = 0; availableX < mapBut[availableY].size(); availableX++)
                        if (abs(selected.second - availableX) <= 2 && abs(selected.first - availableY) <= 4 &&
                            mapBut[availableY][availableX]->getText().getString() == "O") {
                            available = pair<int, int>(availableY, availableX);

                            for (const auto &offset: offsetEnemy) { // for searching possible enemies
                                auto newX = available.first + offset[0];
                                auto newY = available.second + offset[1];
                                counter = 0;

                                if (newX >= 0 && newY < mapBut.size() && newY >= 0 && newX < mapBut[newY].size())
                                    counter++;
                            }
                            choices.insert({pair<pair<int, int>, pair<int, int>>(selected, available),
                                            counter});
                        }
            }
        }

    auto best = std::max_element(choices.begin(), choices.end(),
                                 [](pair<const pair<pair<int, int>, pair<int, int>>, int> firstChoice,
                                    pair<const pair<pair<int, int>, pair<int, int>>, int> secondChoice) -> bool {
                                     return firstChoice.second < secondChoice.second;
                                 });

    mapBut[best->first.first.first][best->first.first.second]->getText().setFillColor(sf::Color::Green);
    checkMove(best->first.second.first, best->first.second.second);
}

auto Game::saveInFile(int player1, int player2) -> void {
    auto result = readFile();
    auto results = vector<vector<int>>();
    auto secondValue = true;
    auto putInFile = std::stringstream();
    auto file = std::ofstream("results.txt");

    auto pattern = std::regex(": (\\d+)");
    auto iss = std::istringstream(result);
    auto match = std::smatch();
    auto line = string();

    while (std::getline(iss, line))
        while (std::regex_search(line, match, pattern)) {
            int value = std::stoi(match[1].str());
            secondValue ? results.push_back({value}) : results.back().push_back(value);
            secondValue = !secondValue;
            line = match.suffix().str();
        }

    results.push_back({player1});
    results.back().push_back(player2);

    std::sort(results.begin(), results.end(),
              [](const vector<int> &first, const vector<int> &second) -> bool {
                  auto nonNullA = 0, nonNullB = 0;

                  if (first[1] != 0)
                      nonNullA = first[1];

                  if (second[1] != 0)
                      nonNullB = second[1];

                  return abs(nonNullA - first[0]) > abs(nonNullB - second[0]);
              });

    if (results.size() == 6)
        results.erase(results.begin() + results.size());

    for (auto &resultInFile: results)
        putInFile << "Player 1: " << resultInFile[0] << "; Player 2: " << resultInFile[1] << '\n';

    file << putInFile.str();

    file.close();
}

auto Game::readFile() -> string {
    auto file = std::ifstream("results.txt");
    auto result = string();
    auto line = string();

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

    file << "Time " << timer.asSeconds() << " Mode " << mode << " Turn " << turn;

    file.close();
}

auto Game::loadGame(const string &path) -> Game {
    auto putInFile = std::stringstream();
    putInFile << "savings/" << path;

    auto file = std::ifstream(putInFile.str());
    auto newMapInt = vector<vector<int>>();
    auto line = string();
    auto turnFrom = false;
    auto modeFrom = false;
    auto varTime = 0.0;

    while (getline(file, line, '\n')) {
        auto tempVec = vector<int>();
        auto ss = std::istringstream(line);

        while (ss >> line)
            if (line == "Time")
                ss >> varTime;
            else if (line == "Mode")
                ss >> modeFrom;
            else if (line == "Turn")
                ss >> turnFrom;
            else
                tempVec.push_back(stoi(line));

        newMapInt.emplace_back(tempVec);
    }

    auto timeString = sf::seconds(varTime);

    file.close();

    return {newMapInt, modeFrom, turnFrom, timeString};
}

auto Game::loadGameBut(const sf::Font &font) -> vector<unique_ptr<Button>> {
    auto newVector = vector<unique_ptr<Button >>();
    auto pos = sf::Vector2f{570, 100};

    for (const auto &entry: std::filesystem::directory_iterator("savings")) {
        auto button = std::make_unique<Button>(entry.path().filename().string(), 70, 13, sf::Color(128, 128, 128), pos,
                                               font, 4);
        newVector.push_back(std::move(button));
        pos.y += 110;
    }

    while (newVector.size() < 6) {
        auto button = std::make_unique<Button>("Empty", 70, 13, sf::Color(128, 128, 128), pos, font, 4);
        newVector.push_back(std::move(button));
        pos.y += 110;
    }

    return newVector;
}