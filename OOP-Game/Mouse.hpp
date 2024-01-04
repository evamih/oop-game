#ifndef MOUSE_HPP
#define MOUSE_HPP
#include "TextureManager.hpp"
#include <SDL.h>

class Mouse {

public: 
	SDL_Renderer* ren;
	SDL_Texture* tex;
	SDL_Rect rect;
	SDL_Rect point;

	Mouse() {
		tex = IMG_LoadTexture(ren, "assets/mouse.png");
		rect.w = 25;
		rect.h = 25;
		point.w = 1;
		point.h = 1;
		SDL_ShowCursor(false);
	}

	void update() {
		SDL_GetMouseState(&rect.x, &rect.y);
		point.x = rect.x;
		point.y = rect.y;
	}

	void draw() {
		SDL_RenderCopy(ren, tex, NULL, &rect);
	}
};


#endif