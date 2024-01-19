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

Button::Button(SDL_Texture* texture, int xpos, int ypos, bool n)
{
	tex = texture;

	srect.h = 43;
	srect.w = 109;
	srect.x = 0;

	drect.h = 43;
	drect.w = 109;
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
		srect.x = 109;
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