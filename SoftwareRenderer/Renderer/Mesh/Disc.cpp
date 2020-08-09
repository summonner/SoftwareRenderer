#include "framework.h"
#include "Disc.h"

namespace Renderer
{
	Disc::Disc( float inner, float outer )
		: inner( inner )
		, outer( outer )
		, start( 0.0f )
		, sweep( 2 * PI )
	{
	}

	Disc::Disc( float inner, float outer, Radian start, Radian sweep )
		: inner( inner )
		, outer( outer )
		, start( start )
		, sweep( sweep )
	{
	}

	Disc::~Disc()
	{
	}

	float Disc::Radius( float t ) const
	{
		return Lerp( inner, outer, t );
	}

	float Disc::Height( float t ) const
	{
		return 0.f;
	}

	Vector3 Disc::Normal( const Vector3& position ) const
	{
		return Vector3::up;
	}

	Radian Disc::Theta( float t ) const
	{
		return start + sweep * t;
	}
}