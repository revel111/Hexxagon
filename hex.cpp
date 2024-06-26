#include "hex.h"

#include <utility>

//const vector <vector<int>> Hex::directions = {
//        {1, 0, -1},
//        {1, -1, 0},
//        {0, 1, -1},
//        {-1, 1, 0},
//        {-1, 0, 1},
//        {0, -1, 1},
//        {2, -2, 0},
//        {2, 0, -2},
//        {0, 2, -2},
//        {-2, 2, 0},
//        {-2, 0, 2},
//        {0, -2, 2},
//        {1, -2, 1},
//        {1, 1, -2},
//        {-1, 2, -1},
//        {-1, -1, 2},
//        {2, -1, -1},
//        {-2, 1, 1}
//};

auto Hex::getQ() const -> int {
    return q;
}

auto Hex::getR() const -> int {
    return r;
}

auto Hex::getS() const -> int {
    return s;
}

auto Hex::getButton() const -> const unique_ptr<Button> & {
    return button;
}

auto Hex::getDistance(const unique_ptr<Hex> &other) const -> int {
    return (abs(q - other->getQ()) + abs(r - other->getR()) + abs(s - other->getS())) / 2;
}

Hex::Hex(int q, int r, int s, unique_ptr<Button> &btn) : q(q), r(r), s(s), button(std::move(btn)) {}

//Hex::Hex(int q, int r, int s) : q(q), r(r), s(s) {}

auto Hex::add(vector<int> offset) const -> vector<int> {
    return {q + offset.at(0), r + offset.at(1), s + offset.at(2)};
}


//vector <vector<int>> Hex::getOffsets() const {
//    vector<vector<int >> offsets;
//
//    for (const auto& offset: directions)
//        offsets.push_back(add(offset));
//
//    return offsets;
//}