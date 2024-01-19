#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.hpp"
#include "Animation.h"
#include "Game.hpp"
#include <map>

class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

	bool isSelected = false;
	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	int animIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(const char* filepath)
	{
		setTexture(filepath);
	}

	SpriteComponent(const char* filepath, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 3, 500);
		Animation walk = Animation(1, 8, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		play("Idle");

		setTexture(filepath);
	}

	SpriteComponent(const char* filepath, bool isAnimated, int time) {
		animated = isAnimated;
		Animation f1 = Animation(0, 2, time);

		animations.emplace("f1", f1);

		play("f1");

		setTexture(filepath);
	}
	//SpriteComponent(const char* filepath, std::string t)
	//{
	//	/*srcRect.y = srcy;
	//	destRect.x = destx;
	//	destRect.y = desty;

	//	srcRect.h = 100;
	//	srcRect.w = 300;
	//	srcRect.x = 10;

	//	destRect.h = 100;
	//	destRect.w = 310;*/

	//	tag = t;

	//	setTexture(filepath);
	//}

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

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.h = transform->height;
		srcRect.w = transform->width;	
	}

	void update() override
	{

		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.h = transform->height * transform->scale;
		destRect.w = transform->width * transform->scale;
	}

	void updateButton(Mouse& mouse, std::string tag) override
	{

		if (SDL_HasIntersection(&destRect, &mouse.point))
		{
			isSelected = true;
			srcRect.x = 52;
			if (tag == "startButton")
			{
				if (Game::event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (SDL_BUTTON_LEFT == Game::event.button.button)
					{
						Game::gameState = "menu2";
					}
				}
			}
			else if (tag == "creditsButton")
			{
				if (Game::event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (SDL_BUTTON_LEFT == Game::event.button.button)
					{
						Game::gameState = "creditsState";
					}
				}
			}
			else if (tag == "leoButton")
			{
				if(Game::event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (SDL_BUTTON_LEFT == Game::event.button.button)
					{
						Game::charTexFile = "assets/animatiiLeo.png";
						Game::gameState = "mainGameState";
					}
				}
			}
			else if (tag == "cleoButton")
			{
				if (Game::event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (SDL_BUTTON_LEFT == Game::event.button.button)
					{
						Game::charTexFile = "assets/animatiiCleo.png";
						Game::gameState = "mainGameState";
					}
				}
			}
		}

		else
		{
			isSelected = false;
			srcRect.x = 0;
		}


	}

	void draw() override
	{
		TextureManager::draw(texture, srcRect, destRect, spriteFlip);
	}

	void play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}

};