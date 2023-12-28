#pragma once
#include "SDL.h"
#include "TextureManager.hpp"
#include <string>

class Map
{
public:
	Map();
	~Map();

	std::string FilePath;
	SDL_Texture* Texture;

	static void loadMap(std::string filepath, int sizeX, int sizeY, int xpos, int ypos);
};
