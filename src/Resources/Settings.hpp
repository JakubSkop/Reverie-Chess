#pragma once

struct FontList{
    sf::Font PrimaryFont{};
    sf::Font SecondaryFont{};
};

struct Settings{
    FontList* fonts;
    sf::Color TintColor1{7*2,47*2,59*2,255};
    double Volume{50.0}; //From 0 to 100;
    bool isMultiplayer = false;
};