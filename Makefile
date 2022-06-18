# -*- MakeFile -*-

all:
	g++ -g -Wall src/*.cpp -I. -I include -lSDL2main -lSDL2 -o build/app
	./build/app

