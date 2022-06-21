#pragma once
#include "Cell.h"

class Renderer
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    RES size;
    Renderer(const char* title, RES size);
    ~Renderer();
    int drawBackGround();
	void setColour(uint8_t R, uint8_t G, uint8_t B);
	void setRandomColour();
	void present();
    void drawCell(std::vector<Cell> &cells);
    void drawRect(SDL_Rect* rect);
};