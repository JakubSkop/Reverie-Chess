#pragma once
#include "Chess/Piece/Pieces.hpp"
#include "General/Constants.hpp"
#include "GridofTiles.hpp"
#include "Chess/Move/Move.hpp"
#include "General/Utilities.hpp"

#include <optional>
#include <bitset>
#include <limits>

using namespace Constants;
enum class printMode{
    TILES,
    PIECE_INDICES,
    PIECE_PLUS_TEAM,
};

class ChessBoard{
    GridofTiles Grid; //Contains an integer that points to a piece in the PieceList, 0 means there is no piece in that position, as well as a tile at each location on the baord
    std::array<Piece, std::numeric_limits<uint8_t>::max()> PieceList = {Pieces::NullFactory()}; //Manages an array of all pieces in the game
    uint8_t last_piece_pointer = 1; //Points to one past where the end of the piecelist is. While it is 256 long, no all of those will be used, so it essentially acts like a static_vector.

    public:
        std::vector<Move> GeneratePseudoLegalMoves_NonCapture(const Piece& piece); //Generate all pseudolegal moves for a piece at an index in the board
        std::vector<Move> GeneratePseudoLegalMoves_Capture(const Piece& piece); //Generate all pseudolegal captures for a piece at an index in the board
        std::vector<Move> GenerateLegalMoves(const Piece& piece);
        std::vector<Move> GenerateAllMoves();
        bool CheckLegality(Move move);
        void Play(Move move);
        void Unplay(Move move); //Allows backtracking up the game tree

        //utility functions
        void Print(printMode pm);
        void AddPiece(Piece p);
        void SetTileMap(Tilemap m);

        const GridofTiles& GetGrid();
        const std::array<Piece, std::numeric_limits<uint8_t>::max()>& GetPieces();

};