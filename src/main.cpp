#include "Renderer.h"

Renderer* pen;

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;

SDL_Event event;

bool isRunning = false;

RES size;

std::vector<Cell> cells;

SDL_Rect *rect;



int init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
	size = getRES();
	pen = new Renderer("Game Of Life", size);

    //initialize variables 

	//populate cells array

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			cells.emplace_back(i, j, new SDL_Rect{j, i, cell_size, cell_size});
		}
	}

	// for(int i = 100; i < 200; i++)
	// 	cells[i].changeState();

    isRunning = true;
	return 0;
}

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
	pen->setColour(0, 0, 0);
	pen->drawBackGround();
	
	pen->drawCell(cells);
    
	pen->present();
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
		
		//debuggggg
		break;
	}

	delete pen;

	return 0;
}