#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponent : public Component
{
public: 
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	const char* filepath;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;
		
		switch (tileID)
		{
		case 0:
			filepath = "assets/ground/tile32.png"; 
			break;
		case 1:
			filepath = "assets/ground/blue32.png";
			break;
		case 2:
			filepath = "assets/ground/green32.png";
			break;
		case 3:
			filepath = "assets/pink32.png";
			break;
		default:
			break;
		}
		
	}

	void init() override
	{
		entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(filepath);
		sprite = &entity->getComponent<SpriteComponent>();
	}
};