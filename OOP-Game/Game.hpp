#pragma once

#include <iostream>
#include "SDL.h" 
#include <iostream>
#include <vector>

class ColliderComponent;

class Game
{
private:
	SDL_Window* window;

public:
	static const char* charTexFile;
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders; //lista de colliders initializate
	static std::string gameState;
	static std::string subject;
	static int count;
	static void second();
	bool isRunning;

	//Game();
	//~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	void openWindow();
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();
	static void quit();

	//void minigameBackground(int id, int x, int y);
};

