#pragma once
#include <SDL2/SDL.h>
#include "utils.h"

class Cell
{
public:
    uint16_t row, col;
    bool active;
    SDL_Rect *rect;

    Cell(uint16_t row, uint16_t col, SDL_Rect* rect);
    Cell();
    void changeState();
};