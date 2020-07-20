#pragma once
#include "RangeIterator.h"

class RangeInt final
{
public:
	RangeInt( int min, int max );

	int Clamp( int value ) const
	{
		return std::clamp( value, min, max );
	}

	inline RangeIterator begin() const
	{
		return RangeIterator( *this, min );
	}

	inline RangeIterator end() const
	{
		return RangeIterator( *this, max );
	}

public:
	int min;
	int max;
};