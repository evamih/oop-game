#include "Button.h"


Button::Button()
{
	static SDL_Texture* t = TextureManager::loadTexture("buttons.png");
	tex = t;

	srect.h = 75;
	srect.w = 300;
	srect.x = 10;

	drect.h = 75;
	drect.w = 300;

}

Button::Button(SDL_Texture* texture, int xpos, int ypos)
{
	tex = texture;

	srect.h = 16;
	srect.w = 17;
	srect.x = 0;

	drect.h = 32;
	drect.w = 34;
	drect.x = xpos;
	drect.y = ypos;

}

//Button::Button(int xpos, int ypos)
//{
//	srect.h = 16;
//	srect.w = 17;
//	srect.x = 0;
//
//	drect.h = 50;
//	drect.w = 34;
//	drect.x = xpos;
//	drect.y = ypos;
//
//}

Button::Button(SDL_Texture* texture, int xpos, int ypos, bool n)
{
	tex = texture;

	srect.h = 79;
	srect.w = 110;
	srect.x = 0;

	drect.h = 79;
	drect.w = 200;
	drect.x = xpos;
	drect.y = ypos;
}

void Button::update(Mouse& mouse)
{
	if (SDL_HasIntersection(&drect, &mouse.point))
	{
		isSelected = true;
		srect.x = 400;
	}
	else {
		isSelected = false;
		srect.x = 0;
	}
}

void Button::update(Mouse& mouse, int flag)
{
	if (SDL_HasIntersection(&drect, &mouse.point))
	{
		isSelected = true;
		srect.x = 17;
	}
	else {
		isSelected = false;
		srect.x = 0;
	}
}

void Button::update(Mouse& mouse, bool n)
{
	if (SDL_HasIntersection(&drect, &mouse.point))
	{
		isSelected = true;
		srect.x = 110;
	}
	else {
		isSelected = false;
		srect.x = 0;
	}
}

void Button::draw()
{
	SDL_RenderCopy(Game::renderer, tex, &srect, &drect);
}