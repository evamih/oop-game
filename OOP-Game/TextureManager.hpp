#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Game.hpp"

class TextureManager
{
private:
	SDL_Texture* ground;

public:
	static SDL_Texture* loadTexture(const char* filePath);
	static void draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};