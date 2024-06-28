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
    int numRows = mapInt.size();

    mapHex.resize(numRows);
    for (int i = 0; i < numRows; ++i)
        mapHex[i].resize(mapInt[i].size());

    auto hexSize = 30.0f;
    auto coords = initializeCoordinates();

    for (int rowIndex = 0; rowIndex < numRows; ++rowIndex) {
        for (int colIndex = 0; colIndex < mapInt[rowIndex].size(); ++colIndex) {

            auto coord = coords.front();
            float posX = window.getSize().x / 2.0f - 25.f + hexSize * 1.5f * coord.getR();
            float posY = window.getSize().y / 2.0f - 30.f +
                         hexSize * std::sqrt(3.0f) * (coord.getQ() + coord.getR() * 0.5f);


            sf::Vector2f pos{posX, posY};
            auto button = std::make_unique<Button>("", hexSize, 10, sf::Color::Black, pos, font, 6);

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


            mapHex[rowIndex][colIndex] = std::make_unique<Hex>(coord.getQ(), coord.getR(), coord.getS(), button);
            coords.erase(coords.begin());
        }
    }
}

auto Game::initializeCoordinates() -> std::deque<Coords> {
    int N = 4;
    auto coords = std::deque<Coords>();

    for (int q = -N; q <= N; q++) {
        int r1 = std::max(-N, -q - N);
        int r2 = std::min(N, -q + N);

        for (int r = r1; r <= r2; r++) {
            auto s = -q - r;
            coords.emplace_back(q, r, s);
        }
    }

    return coords;
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

    for (auto y = 0; y < mapHex.size(); y++)
        for (auto x = 0; x < mapHex[y].size(); x++)
            if (mapHex[y][x]->getButton()->getTextString() == "1" ||
                mapHex[y][x]->getButton()->getTextString() == "2")
                for (auto position: getValidPositions(y, x, 2))
                    if (mapHex[position.first][position.second]->getButton()->getTextString() == "O")
                        return false;

    return true;
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

    if (mapHex[y][x]->getButton()->getText().getFillColor() == sf::Color::Yellow) {
        for (auto position: findEnemies({y, x}))
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
    colorPossible(best->first.first.first, best->first.first.second);
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
            auto pair = find(mapHex[y][x]->add(q, r, -q - r));

            if (pair.first != -1 && pair.second != -1)
                validMoves.push_back(pair);
        }

    return validMoves;
}

auto Game::canMove(int y1, int x1, int y2, int x2) -> int {
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