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

struct PieceBehaviours{
    MoveBehaviour StandardMoveBehaviour;
    MoveBehaviour FirstMoveBehaviour;
    MoveBehaviour StandardAttackBehaviour;
    MoveBehaviour FirstAttackBehaviour;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace PresetBehaviours{
    using namespace DIRECTIONS;

    const PieceBehaviours Null = { { {} , {0,0,0,0,0,0,0,0} }, { {} , {0,0,0,0,0,0,0,0} }, { {} , {0,0,0,0,0,0,0,0} }, { {} , {0,0,0,0,0,0,0,0} } };
    const PieceBehaviours Pawn = { { {DIRECTIONS::FORWARD} , {0,0,0,0,0,0,0,0} }, { {DIRECTIONS::FORWARD, DIRECTIONS::FORWARD+DIRECTIONS::FORWARD} , {0,0,0,0,0,0,0,0} }, 
    {{}  , {0,1,0,0,0,0,0,1}}, {{} , {0,1,0,0,0,0,0,1}} };
    const PieceBehaviours Bishop = { { {} , {0,16,0,16,0,16,0,16} }, { {} , {0,16,0,16,0,16,0,16} }, 
    {{}  , {0,16,0,16,0,16,0,16}}, {{} , {0,16,0,16,0,16,0,16}} };
    const PieceBehaviours Rook = { { {} , {16,0,16,0,16,0,16,0} }, { {} , {16,0,16,0,16,0,16,0} }, 
    {{}  , {16,0,16,0,16,0,16,0}}, {{} , {16,0,16,0,16,0,16,0}} };
    const PieceBehaviours Queen = { { {} , {16,16,16,16,16,16,16,16} }, { {} , {16,16,16,16,16,16,16,16} }, 
    {{}  , {16,16,16,16,16,16,16,16}}, {{} , {16,16,16,16,16,16,16,16}} };
    const PieceBehaviours King = { { {} , {1,1,1,1,1,1,1,1} }, { {} , {1,1,1,1,1,1,1,1} }, 
    {{}  , {1,1,1,1,1,1,1,1}}, {{} , {1,1,1,1,1,1,1,1}} };

    const PieceBehaviours Knight = { { {
        FORWARD+FORWARD+LEFT,
        FORWARD+FORWARD+RIGHT,
        RIGHT+RIGHT+FORWARD,
        RIGHT+RIGHT+BACKWARD,
        LEFT+LEFT+FORWARD,
        LEFT+LEFT+BACKWARD,
        BACKWARD+BACKWARD+LEFT,
        BACKWARD+BACKWARD+RIGHT,
    } , {0,0,0,0,0,0,0,0} }, { {
        FORWARD+FORWARD+LEFT,
        FORWARD+FORWARD+RIGHT,
        RIGHT+RIGHT+FORWARD,
        RIGHT+RIGHT+BACKWARD,
        LEFT+LEFT+FORWARD,
        LEFT+LEFT+BACKWARD,
        BACKWARD+BACKWARD+LEFT,
        BACKWARD+BACKWARD+RIGHT,
    } , {0,0,0,0,0,0,0,0} },{ {
        FORWARD+FORWARD+LEFT,
        FORWARD+FORWARD+RIGHT,
        RIGHT+RIGHT+FORWARD,
        RIGHT+RIGHT+BACKWARD,
        LEFT+LEFT+FORWARD,
        LEFT+LEFT+BACKWARD,
        BACKWARD+BACKWARD+LEFT,
        BACKWARD+BACKWARD+RIGHT,
    } , {0,0,0,0,0,0,0,0} },{ {
        FORWARD+FORWARD+LEFT,
        FORWARD+FORWARD+RIGHT,
        RIGHT+RIGHT+FORWARD,
        RIGHT+RIGHT+BACKWARD,
        LEFT+LEFT+FORWARD,
        LEFT+LEFT+BACKWARD,
        BACKWARD+BACKWARD+LEFT,
        BACKWARD+BACKWARD+RIGHT,
    } , {0,0,0,0,0,0,0,0} } };

    




};

