#include "hex.h"

#include <utility>

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

auto Hex::add(int qq, int rr, int ss) const -> vector<int> {
    return {this->q + qq, this->r + rr, this->s + ss};
}