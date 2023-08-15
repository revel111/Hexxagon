#pragma once

#include "buttonFuncs.h"
#include <vector>


class Map /*: public sf::Drawable, public sf::Transformable*/ {
public:
    static auto draw(sf::RenderWindow &window, const sf::Font &font) -> void;

private:
    static std::vector<std::vector<int>> map;
};