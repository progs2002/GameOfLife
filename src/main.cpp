#include "Renderer.h"

Renderer* pen;

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;

SDL_Event event;

bool isRunning = false;

RES size;

uint8_t cell_size;
uint16_t rows;
uint16_t cols;

std::vector<Cell> cells;

SDL_Rect *rect;



int init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
	size = getRES();
	pen = new Renderer("Game Of Life", size);

    //initialize variables 
	cell_size = 40;
	rows = size.H / cell_size;
	cols = size.W / cell_size;

	//populate cells array
	cells.reserve(rows * cols);
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			cells.emplace_back(i, j, new SDL_Rect{j*cell_size, i*cell_size, cell_size, cell_size});
		}
	}

	//check DEBUG: 
	// for(int i = 0; i < cells.size()/2; i++)	cells[i].changeState();

	isRunning = true;
	return 0;
}

void update()
{
    //handle events

    while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					float x_m = event.button.x;
					float y_m = event.button.y;
					cells[(int)(x_m / cell_size) + rows * (int)(y_m / cell_size)].changeState();
					std::cout << "x:" << x_m << " y:" << y_m << std::endl;
					std::cout << "r:" << (int)x_m/cell_size << " c:" << (int)y_m/cell_size << std::endl;
				}
				break;
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

void cleanUp()
{
	delete pen;
	cells.clear();
}

int main(int argc, char* args[])
{
	init();

	while (isRunning)
	{
		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency()); // in milliseconds
		//std::cout << "Time taken to render in ms = " << deltaTime << std::endl;
		update();
		render();
	}

	cleanUp();

	return 0;
}