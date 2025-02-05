#include "Timer.h"

Timer* Timer::sInstance = NULL;

Timer* Timer::Instance() {
	if (sInstance == NULL) {
		sInstance = new Timer();
	}

	return sInstance;
}
void Timer::Release() {
	delete sInstance;
	sInstance = NULL;
}

Timer::Timer() {
	Reset();
	mTimeScale = 1.0f;
}
Timer::~Timer() {

}

void Timer::Reset() {
	mStartTicks = SDL_GetTicks();
	mElapsedTicks = 0;
	mDeltaTime = 0.0f;
}

float Timer::DeltaTime() {
	return mDeltaTime;
}

unsigned int Timer::startTicks() {
	return mStartTicks;
}

void Timer::TimeScale(float t) {
	mTimeScale = t;
}

float Timer::TimeScale() {
	return mTimeScale;
}

void Timer::Update() {
	mElapsedTicks = SDL_GetTicks() - mStartTicks;
	mDeltaTime = 1.0f;

}