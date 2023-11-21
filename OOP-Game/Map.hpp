#pragma once
#include "SDL.h"
#include "TextureManager.hpp"

class Map
{
private:
	SDL_Rect src;
	SDL_Rect dest;

	SDL_Texture* ground;

public:
	Map();

	void loadMap(int arr[10][10]);
	void drawMap();

	int map[30][30];
};