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

void Button::draw()
{
	SDL_RenderCopy(Game::renderer, tex, &srect, &drect);
}