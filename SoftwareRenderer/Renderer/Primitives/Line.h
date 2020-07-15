#pragma once
#include "IPrimitive.h"

namespace Renderer
{
	class Vertex;
	class Line final : public IPrimitive
	{
	public:
		Line( const Vertex& a, const Vertex& b );
		~Line() override;

		RasterizedPixel Rasterize( const Vector2& coordinate ) const override;

	private:
		struct Result
		{
			float t;
			float squaredDistance;
		};

		Result RasterizeInternal( const Vector2& coordinate ) const;
		RasterizedPixel Lerp( const Vector2& barycentric ) const;

	private:
		const Vertex& a;
		const Vertex& b;
		float squaredThickness;
	};

}