#pragma once

enum class TileType: uint8_t{
    WHITE_PROMOTION = 0,
    BLACK_PROMOTION = 1,
    JOINT_PROMOTION = 2,
    REGULAR = 3,
};

struct Tile{
    bool isActive = false;
    TileType type = TileType::REGULAR;
};