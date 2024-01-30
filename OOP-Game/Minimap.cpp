//#include "Minimap.h"
//#include "Game.hpp"
//#include <fstream>
//
//Minimap::Minimap()
//{
//}
//Minimap::~Minimap()
//{
//}
//
//void Minimap::loadMinimap(std::string filepath, int sizeX, int sizeY, int xpos, int ypos)
//{
//
//	char tile;
//	std::fstream mapFile;
//	mapFile.open(filepath);
//
//	for (int y = ypos; y < sizeY + ypos; y++)
//	{
//		for (int x = xpos; x < sizeX + xpos; x++)
//		{
//			mapFile.get(tile);
//			Game::minigameBackground(atoi(&tile), x * 32, y * 32); //width*scale, height*scale
//			mapFile.ignore();
//		}
//	}
//
//	mapFile.close();
//}
