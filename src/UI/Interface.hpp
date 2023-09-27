#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Resources/ResourcePackage.hpp"


class UpdatesAndDraws{
    public:
        virtual void Draw(Resources appResources) = 0;
        virtual void Update(Resources appResources) = 0;
        virtual ~UpdatesAndDraws() = default;

};