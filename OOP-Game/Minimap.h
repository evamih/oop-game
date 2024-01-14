#pragma once

#include "SDL.h"
#include "TextureManager.hpp"
#include <string>

class Minimap
{
public:
	Minimap();
	~Minimap();

	static void loadMinimap(std::string filepath, int sizeX, int sizeY, int xpos, int ypos);
};
