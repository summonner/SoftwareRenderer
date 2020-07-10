#include "framework.h"
#include "RangeInt.h"

#undef max
#undef min

RangeInt::RangeInt( int min, int max )
	: min( min )
	, max( max )
{}
