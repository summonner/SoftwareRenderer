#include "framework.h"
#include "PlaneIterator.h"

namespace Renderer
{
	const std::vector<PlaneInClip> PlaneIterator::staticPlanes
	{
		PlaneInClip( { 1, 0, 0, 1 } ),
		PlaneInClip( { -1, 0, 0, 1 } ),
		PlaneInClip( { 0, 1, 0, 1 } ),
		PlaneInClip( { 0, -1, 0, 1 } ),
		PlaneInClip( { 0, 0, 1, 1 } ),
		PlaneInClip( { 0, 0, -1, 1 } ),
	};

	PlaneIterator::PlaneIterator( const std::vector<PlaneInView>& customPlanes, unsigned int current )
		: customPlanes( customPlanes )
		, current( current )
	{
	}

	PlaneIterator::~PlaneIterator()
	{
	}

	PlaneIterator PlaneIterator::begin() const
	{
		return PlaneIterator( customPlanes, 0 );
	}

	PlaneIterator PlaneIterator::end() const
	{
		return PlaneIterator( customPlanes, customPlanes.size() + staticPlanes.size() );
	}

	bool PlaneIterator::operator !=( const PlaneIterator& other ) const
	{
		return current != other.current;
	}

	const PlaneIterator& PlaneIterator::operator ++()
	{
		++current;
		return *this;
	}

	const IPlane& PlaneIterator::operator *() const
	{
		const auto numPlanes = customPlanes.size();
		if ( current < numPlanes )
		{
			return customPlanes[current];
		}
		else
		{
			return staticPlanes[current - numPlanes];
		}
	}
}