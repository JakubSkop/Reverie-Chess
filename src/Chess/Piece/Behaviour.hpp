#pragma once

#include "General/Constants.hpp"
#include <vector>
#include <array>

namespace DIRECTIONS{
    constexpr sf::Vector2<int8_t> LEFT{-1,0};
    constexpr sf::Vector2<int8_t> RIGHT{1,0};
    constexpr sf::Vector2<int8_t> FORWARD{0,1};
    constexpr sf::Vector2<int8_t> BACKWARD{0,-1};
};

struct MoveBehaviour{
    std::vector<sf::Vector2<int8_t>> JumpMoves; //Non-sliding moves i.e like horse or pawn
    std::array<uint8_t, 8> SlidingDistances; //The corresponding max distance the piece can slide for each direction: North, NorthEast, East, SouthEast, South, SouthWest, West, NorthWest
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

