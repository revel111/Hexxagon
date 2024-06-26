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
    mapHex.resize(mapInt.size());
    int maxColumns = 0;

    for (const auto &row: mapInt)
        if (row.size() > maxColumns)
            maxColumns = row.size();

    float buttonRadius = 30.0f;
    float buttonSpacingX = buttonRadius * 1.75f;
    float buttonSpacingY = buttonRadius * 1.48f;

    float startX = (1200 - buttonSpacingX * maxColumns) / 2;
    float startY = (800 - buttonSpacingY * (mapInt.size() + 0.5)) / 2;

    int N = mapInt.size() / 2;

    for (int q = -N; q <= N; ++q) {
        int r1 = std::max(-N, -q - N);
        int r2 = std::min(N, -q + N);
        for (int r = r1; r <= r2; ++r) {

            int rowIndex = r + N;
            if (rowIndex < 0 || rowIndex >= mapInt.size()) continue;

            int colIndex = q + (mapInt[rowIndex].size() - 1) / 2;
            if (colIndex < 0 || colIndex >= mapInt[rowIndex].size()) continue;

            float currentStartX = startX + (buttonSpacingX / 2) * (maxColumns - mapInt[rowIndex].size());
            float posX = currentStartX + colIndex * buttonSpacingX;
            float posY = startY + rowIndex * buttonSpacingY;

            sf::Vector2f pos{posX, posY};
            auto button = std::make_unique<Button>("", buttonRadius, 10, sf::Color::Black, pos, font, 6);

            int mapValue = mapInt[rowIndex][colIndex];

            switch (mapValue) {
                case 0:
                    button->getText().setString("X");
                    button->setDefColor(sf::Color(128, 128, 128));
                    break;
                case 1:
                    button->getText().setString("O");
                    button->setDefColor(sf::Color::White);
                    break;
                case 2:
                    button->getText().setString("1");
                    button->setDefColor(sf::Color::Blue);
                    break;
                case 3:
                    button->getText().setString("2");
                    button->setDefColor(sf::Color::Cyan);
                    break;
            }

            button->colorDefault();

            if (mapHex[rowIndex].size() <= colIndex)
                mapHex[rowIndex].resize(colIndex + 1);

            mapHex[rowIndex][colIndex] = std::make_unique<Hex>(q, r, -q - r, button);
            mapHex[rowIndex][colIndex]->getButton()->drawBut(window);
        }
    }
}

auto Game::drawMap(sf::RenderWindow &window) -> void {
    for (auto &i: mapHex)
        for (const auto &j: i)
            j->getButton()->drawBut(window);
}

auto Game::colorGameButtons(sf::RenderWindow &window) -> void {
    for (auto i = 0; i < mapHex.size(); i++)
        for (auto j = 0; j < mapHex[i].size(); j++)
            colorButGame(window, i, j);
}

auto Game::isEnd() -> bool {
    if (counter(1) == "0" || counter(2) == "0" || counter(3) == "0")
        return true;

//    for (auto y = 0; y < mapHex.size(); y++)
//        for (auto x = 0; x < mapHex[y].size(); x++)
//            if (mapHex[y][x]->getButton()->getTextString() == "1" ||
//                mapHex[y][x]->getButton()->getTextString() == "2")
//                for (auto position: getValidPositions(y, x, 2))
//                    if (mapHex[position.first][position.second]->getButton()->getTextString() == "O")
//                        return false;

    return false;
}

auto Game::checkSelected() -> bool {
    for (auto &i: mapHex)
        for (const auto &j: i)
            if (j->getButton()->getText().getFillColor() == sf::Color::Green)
                return true;

    return false;
}

auto Game::colorButGame(sf::RenderWindow &window, int y, int x) -> void {
    if (!mode || (mode && !turn)) {
        sf::Text &text = mapHex[y][x]->getButton()->getText();

        if (mapHex[y][x]->getButton()->isMouseOver(window) && checkSelected())
            if (text.getFillColor() == sf::Color::Green) {
                mapHex[y][x]->getButton()->colorDefault();
                disableColor(sf::Color::Yellow);
            } else
                makeMove(y, x);
        else if (mapHex[y][x]->getButton()->isMouseOver(window)) {
            auto textString = mapHex[y][x]->getButton()->getTextString();

            if ((turn && textString == "2") || (!turn && textString == "1")) {
                mapHex[y][x]->getButton()->color(sf::Color::Green);
                disableColor(sf::Color::Red);
                colorPossible(y, x);
            }
        }
    } else if (mode && turn)
        aiMakeMove();
}

auto Game::makeMove(int y, int x) -> void {
    auto selected = disableColor(sf::Color::Green);

    if (/*canMove(selected.first, selected.second, y, x) &&*/
            mapHex[y][x]->getButton()->getText().getFillColor() == sf::Color::Yellow) {
//        auto validMoves = getValidPositions(selected.first, selected.second, 1);
//        auto validMoves = getValidPositions(selectedY, selectedX);

        for (auto position: findEnemies(selected))
            if (mapHex[position.first][position.second]->getButton()->getTextString() == "2" && !turn) {
                mapHex[position.first][position.second]->getButton()->getText().setString("1");
                mapHex[position.first][position.second]->getButton()->setDefColor(sf::Color::Blue);
                mapHex[position.first][position.second]->getButton()->colorDefault();
            } else if (mapHex[position.first][position.second]->getButton()->getTextString() == "1" && turn) {
                mapHex[position.first][position.second]->getButton()->getText().setString("2");
                mapHex[position.first][position.second]->getButton()->setDefColor(sf::Color::Cyan);
                mapHex[position.first][position.second]->getButton()->colorDefault();
            }

        if (turn) {
            mapHex[y][x]->getButton()->getText().setString("2");
            mapHex[y][x]->getButton()->setDefColor(sf::Color::Cyan);
            mapHex[y][x]->getButton()->colorDefault();
        } else {
            mapHex[y][x]->getButton()->getText().setString("1");
            mapHex[y][x]->getButton()->setDefColor(sf::Color::Blue);
            mapHex[y][x]->getButton()->colorDefault();
        }

        if (canMove(selected.first, selected.second, y, x) == 2) {
            mapHex[selected.first][selected.second]->getButton()->getText().setString("O");
            mapHex[selected.first][selected.second]->getButton()->setDefColor(sf::Color::White);
            mapHex[selected.first][selected.second]->getButton()->colorDefault();
        }

        turn = !turn;
    } else
        mapHex[y][x]->getButton()->color(sf::Color::Red);

    disableColor(sf::Color::Yellow);
}

auto Game::colorPossible(int y, int x) -> void {
//    auto validMoves = getValidPositions(y, x, 2);
//    auto validMoves = getValidPositions(y, x);

    for (auto pair: getValidPositions(y, x, 2))
        if (mapHex[pair.first][pair.second]->getButton()->getTextString() == "O")
            mapHex[pair.first][pair.second]->getButton()->color(sf::Color::Yellow);
}

auto Game::counter(int ch) -> string {
    auto count = 0;

    for (auto &i: mapHex)
        for (const auto &j: i) {
            auto content = j->getButton()->getTextString();

            if ((content == "1" && ch == 1) ||
                (content == "2" && ch == 2) ||
                (content == "O" && ch == 3))
                count++;
        }

    return std::to_string(count);
}

auto Game::aiMakeMove() -> void {
    auto choices = std::map<pair<pair<int, int>, pair<int, int>>, int>();
    auto friendly = pair<int, int>();
    auto available = pair<int, int>();

    for (auto friendY = 0; friendY < mapHex.size(); friendY++)
        for (auto friendX = 0; friendX < mapHex[friendY].size(); friendX++) {
            if (mapHex[friendY][friendX]->getButton()->getText().getString() == "2") {
                friendly = pair<int, int>(friendY, friendX);

                auto validMoves = getValidPositions(friendY, friendX, 2);

                for (auto validMove: validMoves)
                    if (mapHex[validMove.first][validMove.second]->getButton()->getTextString() == "O") {
                        available = pair<int, int>(validMove.first, validMove.second);

                        auto enemies = findEnemies(available);
                        choices.insert({pair<pair<int, int>, pair<int, int>>(friendly, available),
                                        enemies.size()});
                    }
            }
        }

    auto best = std::max_element(choices.begin(), choices.end(),
                                 [](pair<const pair<pair<int, int>, pair<int, int>>, int> firstChoice,
                                    pair<const pair<pair<int, int>, pair<int, int>>, int> secondChoice) -> bool {
                                     return firstChoice.second < secondChoice.second;
                                 });

    mapHex[best->first.first.first][best->first.first.second]->getButton()->color(sf::Color::Green);
    makeMove(best->first.second.first, best->first.second.second);
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

auto Game::disableColor(const sf::Color &colorChange) -> pair<int, int> {
    auto selected = pair<int, int>();

    for (int i = 0; i < mapHex.size(); i++)
        for (int j = 0; j < mapHex[i].size(); j++)
            if (mapHex[i][j]->getButton()->getText().getFillColor() == colorChange) {
                mapHex[i][j]->getButton()->colorDefault();
                selected = {i, j};
            }

    return selected;
}

auto Game::saveGame() -> void {
    auto now = time(nullptr);
    auto putInFile = std::stringstream();
    char timeString[80];

    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H-%M-%S", localtime(&now));

    putInFile << "savings/" << timeString;

    auto file = std::ofstream(putInFile.str());

    for (auto &i: mapHex) {
        for (const auto &j: i) {
            auto text = j->getButton()->getText().getString();

            if (text == "X")
                file << "0 ";
            else if (text == "O")
                file << "1 ";
            else if (text == "1")
                file << "2 ";
            else if (text == "2")
                file << "3 ";
        }
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
    auto pos = sf::Vector2f{570, 80};

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

//auto Game::getValidPositions(int y, int x) -> vector<pair<int, int>> {
//    auto validMoves = vector<pair<int, int>>();
//
//    for (auto i = 0; i < mapHex.size(); i++)
//        for (auto j = 0; j < mapHex[i].size(); j++)
//            if (canMove(i, j, y, x))
//                validMoves.emplace_back(i, j);
//
//    return validMoves;
//}

//auto Game::find(int q, int r, int s) -> pair<int, int> {
auto Game::find(vector<int> coordinates) -> pair<int, int> {
    for (int i = 0; i < mapHex.size(); i++)
        for (int j = 0; j < mapHex[i].size(); j++)
            if (mapHex[i][j]->getQ() == coordinates[0] &&
                mapHex[i][j]->getR() == coordinates[1] &&
                mapHex[i][j]->getS() == coordinates[2])
                return {i, j};

    return {-1, -1};
}

auto Game::getValidPositions(int y, int x, int range) -> vector<pair<int, int>> {
    auto validMoves = vector<pair<int, int>>();

    for (int q = -range; q <= range; q++)
        for (int r = std::max(-range, -q - range); r <= std::min(range, -q + range); r++) {
            auto pair = find(mapHex[y][x]->add({q, r, -q - r}));

            if (pair.first != -1 && pair.second != -1)
                validMoves.push_back(pair);
        }

//    for (int i = 0; i < mapHex.size(); i++)
//        for (int j = 0; j < mapHex[i].size(); j++) {
//            auto distance = canMove(y, x, i, j);
//            if ((range == 2 && (distance == 1 || distance == 2)) ||
//                (range == 1 && distance == 1))
//                validMoves.emplace_back(i, j);
//        }

    return validMoves;
}

auto Game::canMove(int y1, int x1, int y2, int x2) -> int {
//    auto distance = mapHex[y1][x1]->getDistance(mapHex[y2][x2]);
    return mapHex[y1][x1]->getDistance(mapHex[y2][x2]);
}

auto Game::findEnemies(pair<int, int> selected) -> vector<pair<int, int>> {
    auto enemies = vector<pair<int, int>>();

    for (auto position: getValidPositions(selected.first, selected.second, 1))
        if (mapHex[position.first][position.second]->getButton()->getTextString() == "2" && !turn ||
            mapHex[position.first][position.second]->getButton()->getTextString() == "1" && turn)
            enemies.push_back(position);

    return enemies;
}