#pragma once
#include <iostream>
#include "SDL.h"

class Game
{
private:
	SDL_Window* window;
	bool isRunning;

public:
	static SDL_Renderer* renderer;

	//Game();
	//~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();
};

