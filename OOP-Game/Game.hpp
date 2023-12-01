#pragma once
#include <iostream>
#include "SDL.h"
#include "Timer.h"

class Game
{
private:
	SDL_Window* window;
	bool isRunning;

	Timer* mTimer;
	static int FRAME_RATE;

public:
	static SDL_Renderer* renderer;
	
	//Game();
	//~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void countdown();
	void clean();
	bool running();
};

