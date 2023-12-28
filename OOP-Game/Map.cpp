#include "Map.hpp"
#include "Game.hpp"
 #include <fstream>

Map::Map()
{
}
Map::~Map()
{
	
}

void Map::loadMap(std::string filepath, int sizeX, int sizeY, int xpos, int ypos)
{

	char tile; 
	std::fstream mapFile;
	mapFile.open(filepath);

	for(int y = ypos; y < sizeY+ypos; y++)
	{
		for (int x = xpos; x < sizeX+xpos; x++)
		{
			mapFile.get(tile);
			Game::addTile(atoi(&tile), x * 64, y * 64); //width*2, height*2
			mapFile.ignore();
		}
	}

	mapFile.close();
}

