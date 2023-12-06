#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.hpp"

class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

public:

	SpriteComponent() = default;
	SpriteComponent(const char* filepath)
	{
		setTexture(filepath);
	}
	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}
	void setTexture(const char* filepath)
	{
		texture = TextureManager::loadTexture(filepath);
	}
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.h = transform->height;
		srcRect.w = transform->width;	
	}

	void update() override
	{
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.h = transform->height * transform->scale;
		destRect.w = transform->width * transform->scale;
	}

	void draw() override
	{
		TextureManager::draw(texture, srcRect, destRect);
	}

};