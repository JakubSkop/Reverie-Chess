#include "SpriteManager.hpp"
#include <filesystem>
#include <map>
#include <memory>
#include <iostream>

MemSprite SpriteManager::AccessSprite(std::string SpriteName){
    return SpriteList[SpriteName];
};

void SpriteManager::AddSprite(std::string SpriteName, std::string TextureName, sf::IntRect TextureRectangle, float scalingConstant){
    MemSprite sprite;
    sprite.setTexture(*(TextureList.at(TextureName)));
    if (TextureRectangle != sf::IntRect{0,0,0,0}){
        sprite.setTextureRect(TextureRectangle);
    }
    sprite.setScale(scalingConstant, scalingConstant);
    sprite.Forget();

    SpriteList.emplace(SpriteName, sprite);
}

void SpriteManager::AddTexture(std::string filePath, std::string name){
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(filePath)){
        throw std::runtime_error("Couldn't load img from file");
    };
    
    TextureList.try_emplace(name, texture);

};

void SpriteManager::AddFolderOfTextures(std::string directoryPath){
    for (const auto & file : std::filesystem::directory_iterator(directoryPath)) {
        AddTexture(file.path().string(), file.path().stem().string());
    }
};