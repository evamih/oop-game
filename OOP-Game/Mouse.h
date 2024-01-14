#pragma once
#include "Game.hpp"
#include "ECS.h"

class Mouse
{
public:
	//SDL_Texture* tex;
	SDL_Rect rect;
	SDL_Rect point;
	/*TransformComponent* transform;
	SpriteComponent* sprite;*/

	Mouse()
	{
		/*tex = TextureManager::loadTexture("assets/door.png");
		rect.w = wrect;
		rect.h = hrect;*/

		/*transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();*/

		point.w = 1;
		point.h = 1;
		SDL_ShowCursor(false);
	}

	void update()
	{
		SDL_GetMouseState(&rect.x, &rect.y);
		/*transform->position.x = rect.x;
		transform->position.y = rect.y;*/
		point.x = rect.x;
		point.y = rect.y;
	}

	/*void draw()
	{
		SDL_RenderCopy(Game::renderer, tex, NULL, &rect);
	}*/
};