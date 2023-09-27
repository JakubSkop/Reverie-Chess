#include "ElementBuilders.hpp"

template <class T>
Element<T> StaticImage(T Image){
    UI::Element<T> staticImage{Image};
    staticImage.StateStack = {};
    staticImage.StateStack.push(DefaultState<Element<T>>());
    return staticImage;
}