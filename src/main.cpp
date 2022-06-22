#include "Renderer.h"

Renderer* pen;

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;

SDL_Event event;

bool isRunning = false;
bool simStart = false;

RES size;

const uint8_t cell_size = 10;
uint16_t rows;
uint16_t cols;

uint16_t cells_active = 0;

std::vector<Cell> cells;

SDL_Rect *rect;

std::vector<uint32_t> flips;

struct Pos
{
	int x, y;
};

Pos p[8] = {
				{-1,-1},
				{0,-1},
				{1,-1},
				{-1,0},
				{1,0},
				{-1,1},
				{0,1},
				{1,1}

			};

void reset()
{
	for(auto& cell : cells)
		cell.active = false;
}

void invert()
{
	for(auto& cell : cells)
		cell.active = !cell.active;
}

int init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
	size = getRES();
	pen = new Renderer("Game Of Life", size);

    //initialize variables 
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
				if(event.button.button == SDL_BUTTON_LEFT && !simStart)
				{
					float x_m = event.button.x;
					float y_m = event.button.y;
					cells[(int)(x_m / cell_size) + rows * (int)(y_m / cell_size)].changeState();
				}
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_SPACE)
					simStart = !simStart;
				else if(event.key.keysym.sym == SDLK_r)
					reset();
				else if(event.key.keysym.sym == SDLK_s)
					invert();	
				break;
		}
	}

	//logic

	if(!simStart)
		return;

	

	cells_active = 0;

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			int x = j, y = i;

			/*
			RULES
			if cell is active and active_neighbours < 2, cell = inactive
			if cell is active and active_neighbours = {2, 3}, cell = active
			if cell is active and active_neighbours > 3, cell = inactive
			if cell is inactive and active_neighbours = 3, cell = active
			*/

			int active_neighbours = 0;
			int index = rows * y + x;
			
			for(int k = 0; k < 8; k++)
			{
				if(x + p[k].x >= 0 && x + p[k].x < cols && y + p[k].y >= 0 && y + p[k].y < rows)
					active_neighbours += cells[(y + p[k].y)*rows + (x + p[k].x)].active;
			}

			//TODO: Now that we have number of active neighbours its time to calculate the behaviour of our cell. and add it to out flips vector     

			if(cells[x + rows*y].active)
			{
				cells_active ++;

				if(active_neighbours < 2 || active_neighbours > 3)
					flips.push_back(index);
			}
			else if(active_neighbours == 3)
				flips.push_back(index);

		}
	}

	if(!flips.empty())
	{
		for(uint32_t index: flips)
			cells[index].active = !cells[index].active;
		
		flips.clear();
	}

	std::cout << "time to render : "<< deltaTime << "ms cells active : " << cells_active << "\n";
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
		SDL_Delay(100);
	}

	cleanUp();

	return 0;
}