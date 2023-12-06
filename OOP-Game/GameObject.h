#pragma once
#include "Game.hpp"
#include "TextureManager.hpp"
//trebuie sters

class GameObject
{
public:
	GameObject(const char* TextureSheet, int x, int y);
	~GameObject();

	void Update(); //unique functions bcs of specific behaviours
	void Render();

private:

	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

};
 
