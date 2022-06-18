#include "Renderer.h"

Renderer* pen;

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;

SDL_Event event;

bool isRunning = false;

RES size;

void update()
{
    //handle events

    while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
			break;
		}

        //handle single thread inputs
		if (event.type == SDL_KEYDOWN)
		{
			
		}
	}
}

void render()
{
    //display simpleWindow
	pen->setColour(0, 255, 255);
	pen->drawBackGround();
    pen->present();
}

int init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
	size = getRES();
	pen = new Renderer("Window name", size);

    //initialize variables 

    isRunning = true;
	return 0;
}

int main(int argc, char* args[])
{
	init();

	while (isRunning)
	{
		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency()); // in milliseconds
		update();
		render();
	}

	delete pen;

	return 0;
}