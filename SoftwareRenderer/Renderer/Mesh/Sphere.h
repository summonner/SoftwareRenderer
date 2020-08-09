#pragma once
#include "Quadric.h"

namespace Renderer
{
	class Sphere final : public Quadric
	{
	public:
		Sphere( float radius );
		~Sphere() override;

		float Radius( float t ) const override;
		float Height( float t ) const override;
		Vector3 Normal( const Vector3& position ) const override;

	private:
		const float radius;
	};
}