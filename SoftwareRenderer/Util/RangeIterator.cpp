#include "framework.h"
#include "RangeIterator.h"


RangeIterator::RangeIterator( const RangeInt& range, int current )
	: range( range )
	, current( range.Clamp( current ) )
{
}

bool RangeIterator::operator !=( const RangeIterator& other ) const
{
	return current != other.current;
}

const RangeIterator& RangeIterator::operator ++()
{
	if ( current < range.max )
	{
		++current;
	}

	return *this;
}

int RangeIterator::operator *() const
{
	return current;
}