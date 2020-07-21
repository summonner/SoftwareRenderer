#pragma once
#include "IRasterizer.h"
#include "Math/Vector2.hpp"

class RangeInt;
class Bounds;
namespace Renderer
{
	class Bresenham;
	class Vertex;
	class Triangle final : public IRasterizer
	{
	public:
		Triangle( const Vertex& a, const Vertex& b, const Vertex& c );
		~Triangle() override;

		void Rasterize( const Bounds& bounds, ProcessPixel process ) const;

	private:
		static std::vector<const Vertex*> Sort( const Vertex& a, const Vertex& b, const Vertex& c );
		static void Rasterize( const Bounds& bounds, Bresenham* e01, Bresenham* e02, Bresenham* e12, ProcessPixel process );

	private:
		const Vertex& a;
		const Vertex& b;
		const Vertex& c;
	};
}