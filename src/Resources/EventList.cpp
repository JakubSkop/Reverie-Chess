#include "EventList.hpp"
#include "SFML/Window/Event.hpp"
#include <algorithm>
#include <iostream>
using namespace sf;

void EventList::addEvent(Event event){
    if (event.type == Event::EventType::MouseButtonPressed){
        if (event.mouseButton.button == Mouse::Left){
            MouseButtons["Left"] = {true, false, event.mouseButton.x, event.mouseButton.y};
        } else if (event.mouseButton.button == Mouse::Right){
            MouseButtons["Right"] = {true, false, event.mouseButton.x, event.mouseButton.y};
        }
    } else if (event.type == Event::EventType::MouseButtonReleased){
        if (event.mouseButton.button == Mouse::Left){
            MouseButtons["Left"] = {false, true, event.mouseButton.x, event.mouseButton.y};
        } else if (event.mouseButton.button == Mouse::Right){
            MouseButtons["Right"] = {false, true, event.mouseButton.x, event.mouseButton.y};
        }
    } else if (event.type == Event::EventType::MouseWheelScrolled){
        if (event.mouseWheelScroll.wheel == Mouse::Wheel::VerticalWheel){
            MouseWheels["Vertical"] = {event.mouseWheelScroll.delta};
        }
    }
    
}

void EventList::reset(){
    //for (auto p : MouseButtons){
    //    p.second = MouseButtonStates{};
    //}
    for (auto& p : MouseWheels){
        p.second = {0.0f};
    }
    
};