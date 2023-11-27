#include "GameObject.h"
#include "TextureManager.hpp"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
	//renderer = ren;
	objTexture = TextureManager::loadTexture(texturesheet);

	xpos = x;
	ypos = y;
}

void GameObject::Update()
{
	//playerul se misca pe diagonala
	xpos++;
	ypos++;

	srcRect.h = 64;
	srcRect.w = 64;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;

}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}