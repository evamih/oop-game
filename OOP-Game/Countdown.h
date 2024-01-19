#pragma once

#include "Timer.h"
#include "TextureManager.hpp"
#include "ECS.h"
#include <string>
#include <thread>
#include <chrono>

class Countdown : public Component
{
private:
	float timeLeft;
	int startTicks;
	bool isRunning;
	bool isFinished;

	SDL_Rect srcRectBox, destRectBox, srcRectDigits, destRectDigits[4];
	SDL_Texture* boxTexture;
	SDL_Texture* digitsTexture[10];

public:
	Timer* timer;

	Countdown();
	~Countdown();

	void reset();
	//		void render();
	void start(float time);
	void update();

	void loadTextures();
	void loadRects(SDL_Rect dest, float scale);
	void draw() override;

	float getTimeLeft();
	bool getIsRunning();
	bool getIsFinished();


};