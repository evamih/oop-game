#pragma once
#include <SDL.h>
#include "TextureManager.hpp"
#include "Mouse.hpp"

class Button {

public:
	Button(int xpos, int ypos);
	SDL_Rect pos;
	bool isSelected = false;

	~Button();

	void update(Mouse&);
	void draw();

};
