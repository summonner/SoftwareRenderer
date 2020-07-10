#pragma once
#include "IBaseIterator.h"
#include "Math/RangeInt.h"
#include <algorithm>

class RangeIterator : public IBaseIterator<RangeIterator, int>
{
	RangeIterator( const RangeInt& range, int current );

	bool operator !=( const RangeIterator& other ) const;
	const RangeIterator& operator ++();
	int operator *() const;

private:
	int current;
	const RangeInt& range;
};