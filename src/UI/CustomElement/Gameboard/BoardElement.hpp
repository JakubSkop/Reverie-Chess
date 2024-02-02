#pragma once

#include "BoardComponent.hpp"
#include "UI/Element.hpp"
#include "Ui/State.hpp"
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
        GameBoardBuilder(ChessBoard board, sf::Vector2f position, Resources resources, bool startingTeam);
        Element<BoardComponent> getObject();
        void RefreshTiles(sf::Vector2f position, Resources resources);
        void RefreshPieces(Element<BoardComponent>& gameboard1, sf::Vector2f position, Resources resources);

};