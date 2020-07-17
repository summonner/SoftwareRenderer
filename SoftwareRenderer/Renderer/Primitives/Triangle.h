#pragma once
#include "IPrimitive.h"

#include "Math/Vector2.hpp"
namespace Renderer
{
	class Vertex;
	class Triangle final : public IPrimitive
	{
	public:
		Triangle( const Vertex& a, const Vertex& b, const Vertex& c );
		~Triangle() override;

		RasterizedPixel Rasterize( const Vector2& coordinate ) const override;

	private:
		Vector3 Barycentric( const Vector2& coordinate ) const;
		RasterizedPixel Lerp( const Vector3& barycentric ) const;

	private:
		const Vertex& a;
		const Vertex& b;
		const Vertex& c;
	};
}