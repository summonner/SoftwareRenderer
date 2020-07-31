#include "framework.h"
#include "RangeIterator.h"
#include "RangeInt.h"

RangeIterator::RangeIterator( const RangeInt& range, int current )
	: range( range )
	, current( current )
{
	assert( range.min <= range.max );
}

bool RangeIterator::operator !=( const RangeIterator& other ) const
{
	return current != other.current;
}

const RangeIterator& RangeIterator::operator ++()
{
	++current;
	return *this;
}

int RangeIterator::operator *() const
{
	return current;
}