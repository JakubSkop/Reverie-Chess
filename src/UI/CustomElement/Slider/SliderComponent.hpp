#include "UI/CustomSprite/MemSprite.hpp"

template <typename T>
struct Slider{
    MemSprite bar; //bar over which slider slides
    MemSprite handle; //the knob/handle you hold to drag 
    T value; //The value the slider is at;

};
