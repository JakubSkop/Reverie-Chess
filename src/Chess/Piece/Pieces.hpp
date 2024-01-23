#pragma once
#include "Behaviour.hpp"
#include "Information.hpp"

struct PieceInfo{
    std::string_view name;
};


//Class that contains a piece behaviour with some additional data
//Pieces are pure data - all operations are handled by the board
struct Piece{
    sf::Vector2<int8_t> Position;
    PieceBehaviours Behaviour;
    PieceCategory Category;
    PieceInfo information;
    bool Team;
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
    constexpr PieceInfo BishopInfo = {"Basic_Bishop"};
    auto inline BishopFactory = [](sf::Vector2<int8_t> pos, bool team){return Piece{pos, PresetBehaviours::Bishop, PieceCategory::Bishop, BishopInfo, team, false, false };};
    constexpr PieceInfo NullInfo = {""};
    auto inline NullFactory = [](){return Piece{{0,0}, PresetBehaviours::Null, PieceCategory::Pawn, NullInfo, false, false, false };};

};