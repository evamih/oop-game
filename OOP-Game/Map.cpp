#include "Map.hpp"

int l1[10][10] = { 0 };

Map::Map()
{
	ground = TextureManager::loadTexture("assets/ground/tile.png");

	src.x = src.y = 0;
	src.h = src.w = 64;
	dest.h = dest.w = 64;
	dest.x = dest.y = 0;

	loadMap(l1);
}

void Map::loadMap(int arr[10][10])
{
	for (int row = 0; row < 10; row++)
	{
		for (int col = 0; col < 10; col++)
		{
			map[row][col] = l1[row][col];
		}
	}
}

void Map::drawMap()
{
	int type = 0;

	for (int row = 0; row < 10; row++)
	{
		for (int col = 0; col < 10; col++)
		{
			type = map[row][col];

			dest.x = col * 64;
			dest.y = row * 64;

			switch (type)
			{
			case 0:
				TextureManager::draw(ground, src, dest);
				break;
			default:
				break;
			}
		}
	}
}