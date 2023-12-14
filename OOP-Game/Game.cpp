#include "Game.hpp"
#include "Map.hpp"
#include "CountdownRenderer.h"

Map* map;
SDL_Renderer* Game::renderer = nullptr;

CountdownRenderer* _countdown;

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Initialise...\n";

		int flag = 0;

		if (fullscreen)
		{
			flag = SDL_WINDOW_FULLSCREEN;
		}

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flag);

		if (window)
		{
			std::cout << "Window created!\n";
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			std::cout << "Renderer created!\n";
		}

		mTimer = Timer::Instance();

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}


	_countdown = new CountdownRenderer();
	map = new Map();
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update()
{

}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->drawMap();
	this->countdown();
	SDL_RenderPresent(renderer);
}

// ------------- Countdown zone -----------------

void Game::countdown() {

	mTimer->Update();
	
	int secondsLeft=0;
	int minutesLeft=0;

	_countdown->drawCountdownBox();
	const int initialTime = 300;
	if ((mTimer->DeltaTime() - (int)(mTimer->DeltaTime())) >= 0.984f) {

		secondsLeft = initialTime - (int)(mTimer->DeltaTime());
		minutesLeft = secondsLeft / 60;
		secondsLeft %= 60; 

		_countdown->drawCountdown(minutesLeft, secondsLeft);
		printf("%i : %i\n", minutesLeft, secondsLeft);

	}

}

//-------------------------------------------

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	Timer::Release();
	mTimer = NULL;
	SDL_Quit();
	std::cout << "Game cleaned!\n";
}

bool Game::running()
{
	return isRunning;
}