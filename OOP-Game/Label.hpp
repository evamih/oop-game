#pragma once

#include "Game.hpp";
#include "ECS.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

class Label : public Component
{
private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont = "assets/fonts/pixeled/Pixeled.ttf";
	SDL_Color textColor;
	SDL_Texture* labelTexture;

public:
	Label(int xpos, int ypos, std::string text, SDL_Color color, int fontSize)
	{
		textColor = color;
		labelText = text;
		position.x = xpos;
		position.y = ypos;

		setLabelText(fontSize);
	}

	Label(int xpos, int ypos, std::string text, SDL_Color color, int fontSize, int wrappedValue)
	{
		textColor = color;
		labelText = text;
		position.x = xpos;
		position.y = ypos;

		setWrappedLabelText(wrappedValue, fontSize);
	}

	void setWrappedLabelText(int value, int fontSize)
	{
			SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(getFont(fontSize), labelText.c_str(), textColor, value);
			labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surface);
			SDL_FreeSurface(surface);

			SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}

	void setLabelText(int fontSize)
	{
		SDL_Surface* surface = TTF_RenderText_Blended(getFont(fontSize), labelText.c_str(), textColor);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surface);
		SDL_FreeSurface(surface);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}

	void draw() override
	{
		SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
	}

	TTF_Font* getFont(int fontSize)
	{

		TTF_Font* font = TTF_OpenFont(labelFont.c_str(), fontSize);

		if (font == nullptr) {
			std::cout << "ERROR\n";
		}
		else {
			return font;
		}
	}

};