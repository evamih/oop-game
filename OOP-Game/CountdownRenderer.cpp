#include "CountdownRenderer.h"
#include <string>

CountdownRenderer::CountdownRenderer()
{
	timerBox = TextureManager::loadTexture("assets/countdown/box.png");

	src.x = src.y = 0;
	src.h = 32;
	src.w = 64;

	dest.h = 32;
	dest.w = 64;
	dest.x = dest.y = 0;

	loadDigits();
}

void CountdownRenderer::loadDigits()
{
	std::string PATH = "/assets/countdown/";
	
	for (int i = 0; i < 10; i++)
	{
		PATH += std::to_string(i) + ".png";
		timerDigits[i] = TextureManager::loadTexture(PATH.c_str());
	}
}

void CountdownRenderer::drawCountdown(int minutes, int seconds)
{
	TextureManager::draw(timerBox, src, dest);

	src.h =  dest.h  = 28;
	src.w = dest.w = 13;
	dest.x = dest.y = 3;

	TextureManager::draw(timerDigits[(minutes / 10)], src, dest);
	dest.x += dest.w + 3;
	TextureManager::draw(timerDigits[(minutes % 10)], src, dest);
	dest.x += dest.w + 6;
	TextureManager::draw(timerDigits[(seconds / 10)], src, dest);
	dest.x += dest.w + 3;
	TextureManager::draw(timerDigits[(seconds % 10)], src, dest);
}