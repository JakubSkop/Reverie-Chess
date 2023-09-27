#include "Utilities.hpp"

template <class T>
void CenterOrigin(T& sprite){
    sprite.setOrigin(sprite.getGlobalBounds().getSize()/2.0f);
}