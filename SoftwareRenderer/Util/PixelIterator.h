#pragma once
#include "Math/Bounds.h"
#include "Math/Vector2.hpp"
#include "Util/IBaseIterator.h"

class PixelIterator final : public IBaseIterator<PixelIterator, Vector2Int>
{
public:
	PixelIterator( const Bounds& bounds, int x, int y );

	bool operator !=( const PixelIterator& other ) const override;
	const PixelIterator& operator ++() override;
	Vector2Int operator *() const override;

	inline static PixelIterator begin( int width, int height )
	{
		return PixelIterator( Bounds( width, height ), 0, 0 );
	}

	inline static PixelIterator begin( Bounds bounds )
	{
		return PixelIterator( bounds, bounds.x.min, bounds.y.min );
	}

	inline static PixelIterator end( int width, int height )
	{
		return PixelIterator( Bounds( width, height ), 0, height );
	}

	inline static PixelIterator end( Bounds bounds )
	{
		return PixelIterator( bounds, bounds.x.min, bounds.y.max );
	}

private:
	Vector2Int current;
	const Bounds bounds;
};