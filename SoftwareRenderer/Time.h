#pragma once

class Time final
{
public:
	Time();
	~Time();

	void Tick();

	inline float GetDeltaTime() const
	{
		return deltaTime;
	}

	inline float GetTimeFromStart() const
	{
		return currentTickTime - startTime;
	}

private:
	static float GetCurrentSeconds();

private:
	float startTime = 0.f;
	float prevTickTime = 0.f;
	float currentTickTime = 0.f;
	float deltaTime = 0.f;
};

