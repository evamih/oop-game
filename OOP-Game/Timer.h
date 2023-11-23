#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_
#include <SDL.h>

class Timer
{
	private:
		static Timer* sInstance;

		unsigned int mStartTicks;
		unsigned int mElapsedTicks;
		float mDeltaTime;
		float mTimeScale;

	public:
		static Timer* Instance();
		static void Release();

		void Reset();
		float DeltaTime();
		unsigned int startTicks();

		void TimeScale(float t);
		float TimeScale();

		void Update();

	private:
		Timer();
		~Timer();
};

#endif