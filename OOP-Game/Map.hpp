#pragma once
#include "SDL.h"
#include "TextureManager.hpp"
#include <string>

class Map
{
public:
	Map();
	~Map();

	static void loadMap(std::string filepath, int sizeX, int sizeY);
};
