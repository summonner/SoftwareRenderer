#pragma once
#include "IRasterizer.h"
#include "Math/Vector2.hpp"

class RangeInt;
namespace Renderer
{
	class Bresenham;
	class Vertex;
	class Triangle final : public IRasterizer
	{
	public:
		Triangle( const Vertex& a, const Vertex& b, const Vertex& c );
		~Triangle() override;

	private:
		static std::vector<const Vertex*> Sort( const Vertex& a, const Vertex& b, const Vertex& c );
		void Rasterize( const RangeInt&, Bresenham* e01, Bresenham* e02, Bresenham* e12 );
	};
}