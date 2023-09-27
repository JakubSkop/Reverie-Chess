#pragma once

struct Move{
    uint8_t From; //Current Square Index
    uint8_t To; //Square on which the piece will land
    uint8_t Flags; //Falgs for specifying special moves like checks or enPassant.
};