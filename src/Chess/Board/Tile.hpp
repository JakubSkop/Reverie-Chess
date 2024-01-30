#pragma once

enum class TileType: uint8_t{
    REGULAR = 0,
};

struct Tile{
    bool isActive = false;
    bool promoteWhite = false;
    bool promoteBlack = false;
    TileType type = TileType::REGULAR;
};