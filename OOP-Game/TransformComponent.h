#pragma once

#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
public:

	Vector2D position;
	Vector2D velocity;

	int height = 64;
	int width = 64;
	int scale = 2;

	int speed = 3;

	TransformComponent()
	{
		position.zero();
	}//default
		
	TransformComponent(int scale)
	{
		position.zero();
		scale = scale;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int scale)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = scale;
	}

	void init() override
	{
		velocity.zero();
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};
