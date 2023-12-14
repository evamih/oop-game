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
	dest.x = dest.y = 20;

	digitsSrc.x = 0;
	digitsSrc.y = 0;
	digitsSrc.w = 13;
	digitsSrc.h = 28;

	digitsDest[0].x = dest.x + 3;
	digitsDest[0].y = dest.y + 3;
	digitsDest[0].w = 13;
	digitsDest[0].h = 28;

	digitsDest[1].x = digitsDest[0].x + digitsDest[0].w + 3;
	digitsDest[2].x = digitsDest[1].x + digitsDest[1].w + 3;
	digitsDest[3].x = digitsDest[2].x + digitsDest[2].w + 3;

	loadDigits();
}

void CountdownRenderer::loadDigits()
{
	
	for (int i = 0; i < 10; i++)
	{
		std::string PATH = "/assets/countdown/";
		PATH += std::to_string(i) + ".png";
		std::cout << PATH << std::endl;
		timerDigits[i] = TextureManager::loadTexture(PATH.c_str());
	}
}

void CountdownRenderer::drawCountdownBox()
{
	TextureManager::draw(timerBox, src, dest);
}

void CountdownRenderer::drawCountdown(int minutes, int seconds)
{
	TextureManager::draw(timerDigits[(minutes / 10)], digitsSrc, digitsDest[0]);	
	TextureManager::draw(timerDigits[(minutes % 10)], digitsSrc, digitsDest[1]);
	TextureManager::draw(timerDigits[(seconds / 10)], digitsSrc, digitsDest[2]);
	TextureManager::draw(timerDigits[(seconds % 10)], digitsSrc, digitsDest[3]);
}