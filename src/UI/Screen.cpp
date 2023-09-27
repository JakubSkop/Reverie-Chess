#include "Screen.hpp"
#include <iostream>

void Screen::DrawElements(Resources appResources){
    for(auto elem: Elements){
        elem->Draw(appResources);
    };
};

void Screen::UpdateElements(Resources appResources){
    for(auto elem: Elements){
        elem->Update(appResources);
    };
};