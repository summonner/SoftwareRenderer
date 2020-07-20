#pragma once
#include "Util/IBaseIterator.h"

class RangeInt;
class RangeIterator : public IBaseIterator<RangeIterator, int>
{
public:
	RangeIterator( const RangeInt& range, int current );

	bool operator !=( const RangeIterator& other ) const;
	const RangeIterator& operator ++();
	int operator *() const;

private:
	int current;
	const RangeInt& range;
};