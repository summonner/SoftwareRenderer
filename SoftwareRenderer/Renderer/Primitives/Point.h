#pragma once
#include "IPrimitive.h"

namespace Renderer
{
	class Vertex;
	class Point final : public IPrimitive
	{
	public:
		Point( const Vertex& v );
		~Point() override;

		RasterizedPixel Rasterize( const Vector2& coordinate ) const override;

	private:
		bool Contains( const Vector2& coordinate ) const;

	private:
		const Vertex& v;
		float radius;
	};
}