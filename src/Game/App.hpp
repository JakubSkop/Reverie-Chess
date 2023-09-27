#pragma once

#include "Resources/ScreenConductor.hpp"
#include "Resources/SpriteManager.hpp"
#include "Resources/EventList.hpp"
#include "General/Constants.hpp"
#include "Resources/Settings.hpp"

class Application{
    public:
        void GameLoop();
        void Setup();

    private:
        std::unique_ptr<ScreenConductor> Conductor = std::make_unique<ScreenConductor>();
        std::unique_ptr<SpriteManager> SpriteHolder = std::make_unique<SpriteManager>();
        std::unique_ptr<SoundPlayer> audio = std::make_unique<SoundPlayer>();
        sf::RenderWindow Window{sf::VideoMode(Constants::ScreenSize.x, Constants::ScreenSize.y), "Reverie Chess", sf::Style::Close | sf::Style::Titlebar};
        sf::RenderTexture globalTexture{};
        EventList Events;
        sf::Shader shader;

        FontList fonts;
        Settings settings{&fonts};


};