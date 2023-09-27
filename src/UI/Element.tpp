#pragma once
#include "Element.hpp"
#include <iostream>

using namespace UI;

template <class T>
void Element<T>::Draw(Resources appResources){
    StateStack.top()->DrawCallback(this, appResources);
};

template <class T>
void Element<T>::Update(Resources appResources){
    auto NextState = StateStack.top()->UpdateCallback(this, appResources);
    if(NextState.has_value()){
        StateStack.top()->ExitCallback(this);
        StateStack.pop();
        NextState.value()->EnterCallback(this);
        StateStack.push(NextState.value());
    };
};

template <class T>
Element<T>::Element(T drawableComponent){
    DrawableComponent = drawableComponent;
};

template <class T>
void ElementContainer<T>::Draw(Resources appResources){
    for(auto element : SubElements){
        element->Draw(appResources);
    }
}

template <class T>
void ElementContainer<T>::Update(Resources appResources){
    for(auto element : SubElements){
        element->Update(appResources);
    }
}