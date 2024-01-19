#include "Countdown.h"

Countdown::Countdown() {

	timer = Timer::Instance();

	timeLeft = 0.0f;
	isRunning = false;
	isFinished = false;

	loadTextures();
}

Countdown::~Countdown() {

}

void Countdown::reset() {
	timeLeft = 0.0f;
	isRunning = false;
	isFinished = false;
}

void Countdown::start(float time) {

	timeLeft = time;
	//	startTicks = timer->DeltaTime();
	isRunning = true;
	isFinished = false;

	//	this->update();
}

void Countdown::update() {

	if (isRunning) {
		
		timeLeft -= 0.01666f;
		if (timeLeft <= 0.0f) {
			isRunning = false;
			isFinished = true;
		}
	}
}

void Countdown::loadTextures() {
	boxTexture = TextureManager::loadTexture("assets/Countdown/box.png");
	for (int i = 0; i < 10; i++) {
		std::string PATH = "assets/countdown/" + std::to_string(i) + ".png";
		digitsTexture[i] = TextureManager::loadTexture(PATH.c_str());
	}
}

void Countdown::loadRects(SDL_Rect dest, float scale) {
	srcRectBox.x = 0;
	srcRectBox.y = 0;
	srcRectBox.w = 64;
	srcRectBox.h = 32;

	destRectBox.x = dest.x;
	destRectBox.y = dest.y;
	destRectBox.w = srcRectBox.w * scale;
	destRectBox.h = srcRectBox.h * scale;

	srcRectDigits.x = 0;
	srcRectDigits.y = 0;
	srcRectDigits.w = 13;
	srcRectDigits.h = 28;


	destRectDigits[0].x = destRectBox.x + (0) * (destRectBox.w / 5) + 3 * scale;
	destRectDigits[0].y = (destRectBox.y + 1.5f * scale);
	destRectDigits[0].w = srcRectDigits.w * (scale - 0.2f);
	destRectDigits[0].h = srcRectDigits.h * (scale - 0.2f);

	destRectDigits[1].x = destRectBox.x + (1) * (destRectBox.w / 5) + 3 * scale;
	destRectDigits[1].y = (destRectBox.y + 1.5f * scale);
	destRectDigits[1].w = srcRectDigits.w * (scale - 0.2f);
	destRectDigits[1].h = srcRectDigits.h * (scale - 0.2f);

	destRectDigits[2].x = destRectBox.x + (3) * (destRectBox.w / 5) + 3 * scale;
	destRectDigits[2].y = (destRectBox.y + 1.5f * scale);
	destRectDigits[2].w = srcRectDigits.w * (scale - 0.2f);
	destRectDigits[2].h = srcRectDigits.h * (scale - 0.2f);

	destRectDigits[3].x = destRectBox.x + (4) * (destRectBox.w / 5) + 3 * scale;
	destRectDigits[3].y = (destRectBox.y + 1.5f * scale);
	destRectDigits[3].w = srcRectDigits.w * (scale - 0.2f);
	destRectDigits[3].h = srcRectDigits.h * (scale - 0.2f);

}

void Countdown::draw() {

	TextureManager::draw(boxTexture, srcRectBox, destRectBox, SDL_FLIP_NONE);

	TextureManager::draw(digitsTexture[(int)timeLeft / 60 / 10], srcRectDigits, destRectDigits[0], SDL_FLIP_NONE);
	TextureManager::draw(digitsTexture[(int)timeLeft / 60 % 10], srcRectDigits, destRectDigits[1], SDL_FLIP_NONE);
	TextureManager::draw(digitsTexture[(int)timeLeft % 60 / 10], srcRectDigits, destRectDigits[2], SDL_FLIP_NONE);
	TextureManager::draw(digitsTexture[(int)timeLeft % 60 % 10], srcRectDigits, destRectDigits[3], SDL_FLIP_NONE);
}

float Countdown::getTimeLeft() {
	return timeLeft;
}

bool Countdown::getIsRunning() {
	return isRunning;
}

bool Countdown::getIsFinished() {
	return isFinished;
}