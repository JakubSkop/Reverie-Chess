#pragma once

#include "SFML/Window.hpp"
#include <optional>
#include <map>
using namespace sf;

//Serves as a point of access to other parts of the program for checking inputs
//The App class will collect events from the window and place them here every frame
//Stores one of each type of event - adding extra events of the same type overrides the old one
//This should be refreshed and refilled every game loop iteration

struct MouseButtonStates{
    bool Pressed = 0;
    bool Released = 0;
    int x = 0;
    int y = 0;
};

struct MouseWheelStates{
    float delta = 0;
};

class EventList{
    public:
        void addEvent(Event event);
        void reset();

        std::map<std::string, MouseButtonStates> MouseButtons = {{"Left", {}},{"Right", {}}};
        std::map<std::string, MouseWheelStates> MouseWheels = {{"Vertical", {}}};
        
};