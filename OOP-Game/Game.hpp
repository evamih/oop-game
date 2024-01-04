#pragma once
#include <iostream>
#include "SDL.h" 
#include <iostream>
#include <vector>

class ColliderComponent;

class Menu;

class Game
{
private:
	SDL_Window* window;
	bool isRunning;
	

public:
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders; //lista de colliders initializate
	static std::string gameState;
	static void addTile(int id, int x, int y);

	//Game();
	//~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	void openWindow();
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();
	void minigameBackground(int id, int x, int y);
	void initMenu();
	void runMenu();
};

