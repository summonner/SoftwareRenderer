#pragma once
#include "Quadric.h"

namespace Renderer
{
	class Cylinder final : public Quadric
	{
	public:
		Cylinder( float base, float top, float radius );
		~Cylinder() override;

		float Radius( float t ) const override;
		float Height( float t ) const override;
		Vector3 Normal( const Vector3& position ) const override;

	private:
		const float base;
		const float top;
		const float height;
	};
}