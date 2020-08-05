#pragma once

class Degree;
class Radian final
{
public:
	Radian( float radian );
	Radian( const Degree& degree );
	~Radian();

	inline operator float() const
	{
		return value;
	}

private:
	float value;

private:
	static const float DegreeToRadian;
};

