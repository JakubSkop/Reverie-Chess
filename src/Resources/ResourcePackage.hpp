#pragma once

#include "EventList.hpp"
#include "SpriteManager.hpp"
#include "SFML/Window.hpp"
#include "ScreenConductor.hpp"
#include "Settings.hpp"
#include "SoundPlayer.hpp"

struct ScreenConductor; //Forward Declaration to remove cyclic dependency

struct Resources{
    ScreenConductor* screenConductor;
    SpriteManager* spriteManager;
    SoundPlayer* soundPlayer;
    RenderWindow* window;
    RenderTexture* globalTexture;
    EventList* eventList;
    Settings* settings;
    Shader* shader;
};