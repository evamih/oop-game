#pragma once
#include "TextureManager.hpp"
#include "SDL.h"

class CountdownRenderer {
private:
	SDL_Rect src;
	SDL_Rect dest;

	SDL_Texture* timerDigits[10];
	SDL_Texture* timerBox;
public:
	CountdownRenderer();

	void loadDigits();
	void drawCountdown(int minutes, int seconds);

};