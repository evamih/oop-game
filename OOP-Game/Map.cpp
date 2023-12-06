#include "Map.hpp"
#include "Game.hpp"
 #include <fstream>

Map::Map()
{
}
Map::~Map()
{
}

void Map::loadMap(std::string filepath, int sizeX, int sizeY)
{

	char tile; 
	std::fstream mapFile;
	mapFile.open(filepath);

	for(int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			Game::addTile(atoi(&tile), x * 64, y * 64); //width*2, height*2
			mapFile.ignore();
		}
	}

	mapFile.close();
}

