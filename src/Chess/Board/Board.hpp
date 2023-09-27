#pragma once
#include "Chess/Piece/Pieces.hpp"
#include "General/Constants.hpp"
#include "Tile.hpp"
#include "Chess/Move/Move.hpp"
#include "General/Utilities.hpp"

#include <bitset>
#include <limits>

using namespace Constants;

class Board{
    std::array<uint8_t, MAX_BOARD_SIZE> MainBoard; //Contains an integer that points to a piece in the PieceList, -1 means there is no piece in that position
    std::array<Piece, std::numeric_limits<uint8_t>::max()> PieceList; //Every piece contains a key to a pieceBehaviour is the below array, among other things
    std::array<PieceBehaviours, std::numeric_limits<uint8_t>::max()> PieceBehaviourList;
    std::array<Tile, MAX_BOARD_SIZE> TileList;

    std::bitset<MAX_BOARD_SIZE> PiecesInCheck;
    std::bitset<MAX_BOARD_SIZE> PiecesFrozen;

    public:
        std::vector<Move> GeneratePseudoLegalMoves(Piece P);
        std::vector<Move> GenerateLegalMoves(Piece P);
        std::vector<Move> GenerateAllMoves(Piece P);

    

};