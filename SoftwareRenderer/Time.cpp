#include "framework.h"
#include "Time.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

Time::Time()
{
	Tick();
}


Time::~Time()
{
}

void Time::Tick()
{
	prevTickTime = currentTickTime;
	currentTickTime = timeGetTime() * 0.001f;
	deltaTime = currentTickTime - prevTickTime;
}