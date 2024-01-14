#pragma once

#include "Game.hpp"
#include "ECS.h"
#include "Components.h"

class MouseController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	//SDL_Rect point;
	int x, y;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		SDL_ShowCursor(false);
		/*point.h = 1;
		point.w = 1*/;
	}

	void update() override
	{
		SDL_GetMouseState(&x, &y);
		transform->position.x = x;
		transform->position.y = y;
		/*point.x = x;
		point.y = y;*/
	}
};
