#include "Pieces.hpp"

uint8_t VecToIndex(sf::Vector2<int8_t> Position){
    return Position.y*16 + Position.x;
}

sf::Vector2<int8_t> IndexToVec(uint8_t Position){
    return sf::Vector2<int8_t>(Position%16,Position/16);
}