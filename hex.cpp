#include "hex.h"

#include <utility>

int Hex::getQ() const {
    return q;
}

int Hex::getR() const {
    return r;
}

int Hex::getS() const {
    return s;
}

const Button &Hex::getButton() const {
    return button;
}

Hex::Hex(int q, int r, int s, Button button) : q(q), r(r), s(s), button(std::move(button)) {}

int Hex::getDistance(const Hex &other) const {
    return (abs(q - other.getQ()) + abs(r - other.getR()) + abs(s - other.getS()));
}
