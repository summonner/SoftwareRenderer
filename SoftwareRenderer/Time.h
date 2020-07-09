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

private:
	float prevTickTime = 0.f;
	float currentTickTime = 0.f;
	float deltaTime = 0.f;
};

