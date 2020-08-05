#pragma once

class Radian;
class Degree final
{
public:
	Degree( float degree );
	Degree( const Radian& radian );
	~Degree();

	inline operator float() const
	{
		return value;
	}

private:
	float value;

	static const float RadianToDegree;
};

