#include "framework.h"
#include "Time.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

Time::Time()
	: startTime( GetCurrentSeconds() )
{
	Tick();
}


Time::~Time()
{
}

void Time::Tick()
{
	prevTickTime = currentTickTime;
	currentTickTime = GetCurrentSeconds();
	deltaTime = currentTickTime - prevTickTime;
}

float Time::GetCurrentSeconds()
{
	return timeGetTime() * 0.001f;
}