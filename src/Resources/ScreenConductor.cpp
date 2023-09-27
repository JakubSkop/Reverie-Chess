#include "ScreenConductor.hpp"
#include <iostream>

void ScreenConductor::PushScreen(const std::string& key){
    auto screen = MapOfScreens.at(key);
    screen->PushCallback();
    ScreenStack.push_back(screen);
}

void ScreenConductor::PopScreen(){ //Requests a pop, but leaves execution till the next update, in which it is safe to do so
    PopCounter++;
}

void ScreenConductor::UpdateScreens(Resources appResources){
    while (PopCounter != 0){
        ScreenStack.pop_back();
        PopCounter--;
    }

    auto it = ScreenStack.size()-1;
    for (it; it != -1; --it){
        if (ScreenStack.at(it)->UpdateUnder == false){
            break;
        }
    }
    for (it; it != ScreenStack.size(); ++it){
        ScreenStack.at(it)->UpdateElements(appResources);
    }
}

void ScreenConductor::DrawScreens(Resources appResources){
    auto it = ScreenStack.size()-1;
    for (it; it != -1; --it){
        if (ScreenStack.at(it)->DrawUnder == false){
            break;
        }
    }
    for (it; it != ScreenStack.size(); ++it){
        ScreenStack.at(it)->DrawElements(appResources);
    }
};

void ScreenConductor::AddPotentialScreens(std::initializer_list<std::pair<const std::string, std::shared_ptr<Screen>>> KeysForScreens){
    for (auto i: KeysForScreens){
        MapOfScreens.emplace(i);
    }
};

