#include "framework.h"
#include "BresenhamCircle.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	BresenhamCircle::BresenhamCircle( const Vector2Int& center, float radius )
		: c( center )
		, r( radius )
		, d( (int)(3 - 2 * r) )
		, next( 1, 1 )
		, add( 2, 0 )
		, _p( 0, (int)-r )
		, p( _p )
	{
	}

	BresenhamCircle::~BresenhamCircle()
	{
	}

	bool BresenhamCircle::Next()
	{
		if ( d * next.x <= 0 )
		{
			d += 4 * _p.x * next.x + 4 + add.x;
			_p.x += next.x;
		}

		if ( d * next.x >= 0 )
		{
			d += 4 * _p.y + 4 + add.y;
			_p.y += next.y;
		}

		if ( _p.y == 0 )
		{
			next.x *= -1;
			d = (int)(3 - 2 * r);
			add = Vector2Int( 0, 2 );
		}

		return (_p.y < r) && (_p.x >= 0);
	}

	bool BresenhamCircle::NextY()
	{
		auto y = p.y;
		auto cont = true;
		while ( y >= p.y && cont )
		{
			cont = Next();
		}

		return cont;
	}
}