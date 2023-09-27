#pragma once

#include "SFML/Graphics.hpp"
#include <map>
#include <memory>
#include "UI/CustomSprite/MemSprite.hpp"

class SpriteManager{
    public:
        MemSprite AccessSprite(std::string SpriteName);
        void AddFolderOfTextures(std::string directoryPath);
        void AddSprite(std::string SpriteName, std::string TextureName, sf::IntRect TextureRectangle = {0,0,0,0}, float scalingConstant = 1.0);

    private:
        void AddTexture(std::string filePath, std::string name);
        std::map<std::string, MemSprite> SpriteList;
        std::map<std::string, std::shared_ptr<sf::Texture>> TextureList;
    
};