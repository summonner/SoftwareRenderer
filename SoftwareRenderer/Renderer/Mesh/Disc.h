#pragma once
#include "Quadric.h"

namespace Renderer
{
	class Disc final : public Quadric
	{
	public:
		Disc( float inner, float outer );
		Disc( float inner, float outer, Radian start, Radian sweep );
		~Disc() override;

		float Radius( float t ) const override;
		float Height( float t ) const override;
		Vector2 Texcoord( float tSlices, float tStacks ) const override;
		Vector3 Normal( const Vector3& position ) const override;
		Radian Theta( float t ) const override;

	private:
		const float inner;
		const float outer;
		const Radian start;
		const Radian sweep;
	};
}