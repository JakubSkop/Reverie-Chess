#pragma once

#include "Constants.hpp"
#include "SFML/System/Vector2.hpp"


constexpr int operator ""_perW(long double percentage){
    return (Constants::ScreenSize.x * percentage)/100;
};

constexpr int operator ""_perH(long double percentage){
    return (Constants::ScreenSize.y * percentage)/100;
};

uint8_t PositionToIndex(sf::Vector2<uint8_t> Pos);

template <class T>
void CenterOrigin(T& sprite);






#include "Utilities.tpp"