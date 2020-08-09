#include "framework.h"
#include "Sphere.h"

namespace Renderer
{
	Sphere::Sphere( float radius )
		: radius( radius )
	{
	}

	Sphere::~Sphere()
	{
	}

	float Sphere::Radius( float t ) const
	{
		return sin( t * PI );
	}

	float Sphere::Height( float t ) const
	{
		return cos( t * PI );
	}

	Vector2 Sphere::Texcoord( float tSlices, float tStacks ) const
	{
		const float v = cos( tStacks * PI );
		return Vector2( 1 - tSlices, 1 - tStacks );
	}

	Vector3 Sphere::Normal( const Vector3& position ) const
	{
		return position;
	}
}