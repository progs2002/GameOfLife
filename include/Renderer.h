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
	void setColour(int R, int G, int B);
	void setRandomColour();
	void present();
    void showAxis();
    void plot(float(*func)(float));
    void joinPoints(std::vector<Point*>& points);
    void join(Point& p1, Point& p2);
    void drawCell(std::vector<Cell> &cells);
    void drawRect(SDL_Rect* rect);
};