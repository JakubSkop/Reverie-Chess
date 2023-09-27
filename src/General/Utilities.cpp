#include "Utilities.hpp"

uint8_t PositionToIndex(sf::Vector2<uint8_t> Pos){
    return 16*Pos.y + Pos.x;
};