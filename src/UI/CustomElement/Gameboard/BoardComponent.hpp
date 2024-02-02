#pragma once

#include "UI/Element.hpp"
#include "Chess/Board/Board.hpp"
#include "Chess/Piece/Pieces.hpp"
#include "General/Constants.hpp"

struct BoardComponent{
    ChessBoard Board;
    sf::Vector2i CurrentLocation;
    bool currentTeam;
    std::vector<Move> currentMoves;
    std::array<MemSprite, Constants::MAX_BOARD_SIZE> Tiles;
    std::vector<MemSprite> PromotionOverlay;
    std::array<MemSprite, Constants::MAX_BOARD_SIZE> Pieces;
    MemSprite CurrentPieceOverlay;
    std::array<MemSprite, Constants::MAX_BOARD_SIZE> PossibleMoves;
    sf::Text Winner;
};

