#pragma once
#include "IPlane.h"

namespace Renderer
{
	class PlaneInClip final : public IPlane
	{
	public:
		PlaneInClip( const Vector4& coefficients );
		~PlaneInClip() override;

		float Dot( const Vertex& vertex ) const override;
		float DotWithDiff( const Vertex& v1, const Vertex& v2 ) const override;

	private:
		const Vector4 coefficients;
	};
}
