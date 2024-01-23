#pragma once

#include "BoardComponent.hpp"
#include "Element.hpp"
#include "State.hpp"
#include <chrono>
#include "UI/CustomSprite/MemSprite.hpp"
#include "General/Constants.hpp"
#include "Resources/ResourcePackage.hpp"

#include <memory>

using PotentialStatePtr = std::optional<std::shared_ptr<State<Element<BoardComponent>>>>;
using StatePtr = std::shared_ptr<State<Element<BoardComponent>>>;

class GameBoardBuilder{
    Element<BoardComponent> gameboard;

    public:
        GameBoardBuilder(ChessBoard board, sf::Vector2f position, Resources resources);
        Element<BoardComponent> getObject();
};