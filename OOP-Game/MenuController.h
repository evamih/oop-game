#pragma once

#include "Game.hpp"
#include "ECS.h"

class MenuController : public Component
{
public:

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_SPACE:
				Game::gameState = "mainGameState";
				break;
			}
		}
	}
};