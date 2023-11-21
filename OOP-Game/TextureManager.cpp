#include "TextureManager.hpp"

SDL_Texture* TextureManager::loadTexture(const char* filePath)
{
	SDL_Surface* tmpSurface = IMG_Load(filePath);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return texture;
}

void TextureManager::draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}