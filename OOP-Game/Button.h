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
	//Button(SDL_Texture* texture, int xpos, int ypos, bool, bool);
	//Button(SDL_Texture* texture, int xpos, int ypos, bool, int);

	void update(Mouse&);
	void update(Mouse&, int);
	void update(Mouse&, bool);
	void update(Mouse&, bool, bool);
	void update(Mouse&, bool, int);
	void draw();

};