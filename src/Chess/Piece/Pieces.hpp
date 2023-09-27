#pragma once
#include "Behaviour.hpp"
#include "Information.hpp"

enum class Colour : uint8_t{
    White,
    Black,
    Neutral,
};

struct PieceBehaviours{
    MoveBehaviour StandardMoveBehaviour;
    MoveBehaviour FirstMoveBehaviour;
};

//Class that contains a piece behaviour with some additional data
//Pieces are pure data - all operations are handled by the board
struct Piece{
    sf::Vector2<uint8_t> Position;
    PieceCategory Category;
    Colour Team;
    bool HasMoved;
    bool Indestructible;
    uint8_t BehaviourIndex; //Holds an index to a behaviour in the board PieceBehaviourList
};
//7 bytes large right now

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////