#pragma once

#include "Game.hpp"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;


	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override
	{

		/*if (Game::event.type == SDL_MOUSEMOTION)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);

			std::cout << x << " : " << y << std::endl;
		}
		if (Game::event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (SDL_BUTTON_LEFT == Game::event.button.button)
			{
				std::cout << "left mouse button is down" << std::endl;
			}
		}*/

		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->play("Walk");
				break;

			case SDLK_RIGHT:
				transform->velocity.x = 1;
				sprite->play("Walk");
				break;

			case SDLK_s:
				transform->velocity.y = 1;
				sprite->play("Walk");
				break;

			case SDLK_DOWN:
				transform->velocity.y = 1;
				sprite->play("Walk");
				break;

			case SDLK_a:
				transform->velocity.x = -1;
				sprite->play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;

			case SDLK_LEFT:
				transform->velocity.x = -1;
				sprite->play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;

			case SDLK_w:
				transform->velocity.y = -1;
				sprite->play("Walk");
				break;

			case SDLK_UP:
				transform->velocity.y = -1;
				sprite->play("Walk");
				break;

			case SDLK_y:
				Game::gameState = "mainGameState";
				//case SDLK_x: minigame::quit = true

			/*case SDLK_ESCAPE:
				Game::isRunning = false;*/

			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->play("Idle");
				break;

			case SDLK_RIGHT:
				transform->velocity.x = 0;
				sprite->play("Idle");
				break;

			case SDLK_s:
				transform->velocity.y = 0;
				sprite->play("Idle");
				break;

			case SDLK_DOWN:
				transform->velocity.y = 0;
				sprite->play("Idle");
				break;

			case SDLK_a:
				transform->velocity.x = 0;
				sprite->play("Idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;

			case SDLK_LEFT:
				transform->velocity.x = 0;
				sprite->play("Idle");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;

			case SDLK_w:
				transform->velocity.y = 0;
				sprite->play("Idle");
				break;

			case SDLK_UP:
				transform->velocity.y = 0;
				sprite->play("Idle");
				break;


			default:
				break;
			}
		}
	}
};