#include "Coords.h"

Coords::Coords(int q, int r, int s) {
    this->q = q;
    this->r = r;
    this->s = s;
}

auto Coords::getQ() const -> int {
    return q;
}

auto Coords::getR() const -> int {
    return r;
}

auto Coords::getS() const -> int {
    return s;
}