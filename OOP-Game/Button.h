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
	Button(SDL_Texture* texture, int xpos, int ypos);
	Button(SDL_Texture* texture, int xpos, int ypos, bool);
	
	void update(Mouse&);
	void update(Mouse&, int);
	void update(Mouse&, bool);
	void draw();

};