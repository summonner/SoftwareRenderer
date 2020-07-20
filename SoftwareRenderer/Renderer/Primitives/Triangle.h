#pragma once
#include "IPrimitive.h"
#include "Math/Vector2.hpp"

class RangeInt;
namespace Renderer
{
	class Bresenham;
	class Vertex;
	class Triangle final : public IPrimitive
	{
	public:
		Triangle( const Vertex& a, const Vertex& b, const Vertex& c );
		~Triangle() override;

		RasterizedPixel Rasterize( const Vector2& coordinate ) const override;

	private:
		static std::vector<const Vertex*> Sort( const Vertex& a, const Vertex& b, const Vertex& c );
		void Rasterize( const RangeInt&, Bresenham* e01, Bresenham* e02, Bresenham* e12 );

		Vector3 Barycentric( const Vector2& coordinate ) const;
		RasterizedPixel Lerp( const Vector3& barycentric ) const;

	private:
		const Vertex& a;
		const Vertex& b;
		const Vertex& c;
	};
}