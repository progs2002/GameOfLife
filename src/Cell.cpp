#include "Cell.h"


Cell::Cell(uint16_t row, uint16_t col, SDL_Rect* rect)
: row(row), col(col), rect(rect)
{
    this->active = false;
}

Cell::Cell()
: row(-1), col(-1)
{
    this->active = false;
    this->rect = nullptr;
}

void Cell::changeState()
{
    this->active = !active;
}

