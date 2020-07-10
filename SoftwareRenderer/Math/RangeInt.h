#pragma once

class RangeInt
{
public:
	RangeInt( int min, int max );

	int Clamp( int value ) const
	{
		return std::clamp( value, min, max );
	}

public:
	int min;
	int max;
};