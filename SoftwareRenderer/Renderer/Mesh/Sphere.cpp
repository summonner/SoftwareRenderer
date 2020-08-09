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

	Vector3 Sphere::Normal( const Vector3& position ) const
	{
		return position;
	}
}