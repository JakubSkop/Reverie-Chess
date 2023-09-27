#pragma once

#include <vector>
#include <map>
#include "UI/Screen.hpp"

struct Screen;
struct Resources;

class ScreenConductor{
    public:
        void PushScreen(const std::string& key);
        void PopScreen();
        void UpdateScreens(Resources appResources);
        void DrawScreens(Resources appResources);
        void AddPotentialScreens(std::initializer_list<std::pair<const std::string, std::shared_ptr<Screen>>> KeysForScreens);

    private:
        std::vector<std::shared_ptr<Screen>> ScreenStack;
        std::map<std::string, std::shared_ptr<Screen>> MapOfScreens;
        uint8_t PopCounter; //Keeps Track of how many pops have been requested asince the last update
};