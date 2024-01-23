#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdint>

struct Move{
    uint8_t from; //Current Square Index
    uint8_t to; //Square on which the piece will land
    uint8_t captureIndex;
    bool promotion = false;
    bool castle = false;
    bool firstMove = false;
};
//In the Case of castling moves, the encoding behaves slightly different - the from index represnts the kings poisition, and the to index represent the rook's position

std::ostream& operator<<(std::ostream& os, Move m);


