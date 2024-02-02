#pragma once
#include "Behaviour.hpp"
#include "Information.hpp"

struct PieceInfo{
    std::string name;
};


//Class that contains a piece behaviour with some additional data
//Pieces are pure data - all operations are handled by the board
struct Piece{
    sf::Vector2<int8_t> Position;
    PieceBehaviours Behaviour;
    PieceCategory Category;
    PieceInfo information;
    bool Team; //black is true
    bool HasMoved;
    bool InCheck;
    bool Alive = true;
};

uint8_t VecToIndex(sf::Vector2<int8_t> Position);

sf::Vector2<int8_t> IndexToVec(uint8_t Position);

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


namespace Pieces{
    constexpr PieceInfo PawnInfo = {"Basic_Pawn"};
    auto inline PawnFactory = [](sf::Vector2<int8_t> pos, bool team){return Piece{pos, PresetBehaviours::Pawn, PieceCategory::Pawn, PawnInfo, team, false, false };};
    constexpr PieceInfo KnightInfo = {"Basic_Knight"};
    auto inline KnightFactory = [](sf::Vector2<int8_t> pos, bool team){return Piece{pos, PresetBehaviours::Knight, PieceCategory::Knight, KnightInfo, team, false, false };};
    constexpr PieceInfo BishopInfo = {"Basic_Bishop"};
    auto inline BishopFactory = [](sf::Vector2<int8_t> pos, bool team){return Piece{pos, PresetBehaviours::Bishop, PieceCategory::Bishop, BishopInfo, team, false, false };};
    constexpr PieceInfo RookInfo = {"Basic_Rook"};
    auto inline RookFactory = [](sf::Vector2<int8_t> pos, bool team){return Piece{pos, PresetBehaviours::Rook, PieceCategory::Rook, RookInfo, team, false, false };};
    constexpr PieceInfo QueenInfo = {"Basic_Queen"};
    auto inline QueenFactory = [](sf::Vector2<int8_t> pos, bool team){return Piece{pos, PresetBehaviours::Queen, PieceCategory::Queen, QueenInfo, team, false, false };};
    constexpr PieceInfo KingInfo = {"Basic_King"};
    auto inline KingFactory = [](sf::Vector2<int8_t> pos, bool team){return Piece{pos, PresetBehaviours::King, PieceCategory::King, KingInfo, team, false, false };};
    constexpr PieceInfo NullInfo = {"Null"};
    auto inline NullFactory = [](){return Piece{{0,0}, PresetBehaviours::Null, PieceCategory::Pawn, NullInfo, false, false, false };};

};