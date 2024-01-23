#include "Move.hpp"
#include "../Piece/Pieces.hpp"
#include <iostream>


std::ostream& operator<<(std::ostream& os, Move m){
    auto from = IndexToVec(m.from);
    auto to = IndexToVec(m.to);
    os << "{From: " << int{from.x} << ", " << int{from.y} << ", To: " << int{to.x} << ", " << int{to.y} << "}" << " - Capture: " << int{m.captureIndex};
    return os;
};