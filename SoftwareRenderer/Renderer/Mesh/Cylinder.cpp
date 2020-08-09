#include "framework.h"
#include "Cylinder.h"

namespace Renderer
{
	Cylinder::Cylinder( float base, float top, float height )
		: base( base )
		, top( top )
		, height( height )
	{
	}

	Cylinder::~Cylinder()
	{
	}

	float Cylinder::Radius( float t ) const
	{
		return Lerp( base, top, t );
	}

	float Cylinder::Height( float t ) const
	{
		return height * (1 - t);
	}

	Vector2 Cylinder::Texcoord( float tSlices, float tStacks ) const
	{
		return Vector2( 1 - tSlices, 1 - tStacks );
	}

	Vector3 Cylinder::Normal( const Vector3& position ) const
	{
		return Vector3( position.x, position.y, 0.f );
	}
}