#include "framework.h"
#include "Timer.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

Timer::Timer()
	: startTime( GetCurrentSeconds() )
{
	Tick();
}


Timer::~Timer()
{
}

void Timer::Tick()
{
	prevTickTime = currentTickTime;
	currentTickTime = GetCurrentSeconds();
	deltaTime = currentTickTime - prevTickTime;
}

float Timer::GetCurrentSeconds()
{
	return timeGetTime() * 0.001f;
}