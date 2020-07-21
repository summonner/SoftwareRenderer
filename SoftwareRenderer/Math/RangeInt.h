#pragma once
#include "RangeIterator.h"

class RangeInt final
{
public:
	RangeInt( int min, int max );

	inline int Clamp( int value ) const
	{
		return std::clamp( value, min, max );
	}

	inline RangeInt Clamp( const RangeInt& subject ) const
	{
		return Clamp( subject.min, subject.max );
	}

	inline RangeInt Clamp( int subjectMin, int subjectMax ) const
	{
		return RangeInt( Clamp( subjectMin ), Clamp( subjectMax ) );
	}

	inline bool Contains( int p ) const
	{
		return p >= min
			&& p <= max;
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