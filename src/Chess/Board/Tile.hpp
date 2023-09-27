#pragma once

enum class Tile: uint8_t{
    Active,
    Inactive,
    WhitePromotion,
    BlackPromotion,
    SharedPromotion,
};