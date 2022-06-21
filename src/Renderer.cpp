#include "Renderer.h"

Renderer::Renderer(const char* title, RES size)
{
	this->size = size;
	window = SDL_CreateWindow(title , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.W, size.H, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	std::cout << "===========================" << std::endl;
	std::cout << "deleted window and renderer" << std::endl;
	std::cout << "===========================" << std::endl;
}

int Renderer::drawBackGround()
{
	SDL_RenderClear(renderer);
	return 1;
}

void Renderer::setColour(uint8_t R, uint8_t G, uint8_t B)
{
	SDL_SetRenderDrawColor(renderer, R, G, B, SDL_ALPHA_OPAQUE);
}

void Renderer::present()
{
	SDL_RenderPresent(renderer);
}

void Renderer::drawCell(std::vector<Cell> &cells)
{
	for(auto cell : cells)
	{
		if(cell.active)
			setColour(255,255,255);
		else
			setColour(0,0,0);
		drawRect(cell.rect);
	}
}

void Renderer::drawRect(SDL_Rect* rect)
{
	SDL_RenderFillRect(renderer, rect);
}
