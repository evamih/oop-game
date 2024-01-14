#pragma once
#include "TextureManager.hpp"
#include "Mouse.h"

class Button 
{
public:
	SDL_Texture* tex;
	SDL_Rect srect, drect;
	bool isSelected = false;

	Button();
	
	void update(Mouse&);
	void draw();

};