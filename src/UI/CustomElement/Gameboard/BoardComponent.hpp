#pragma once

#include "UI/Element.hpp"
#include "Chess/Board/Board.hpp"
#include "Chess/Piece/Pieces.hpp"
#include "General/Constants.hpp"

struct BoardComponent{
    ChessBoard Board;
    std::array<MemSprite, Constants::MAX_BOARD_SIZE> Tiles;
    std::vector<MemSprite> Pieces;
    MemSprite CurrentPiece;
    std::vector<MemSprite> PossibleMoves;
};

