#pragma once
#include "IRasterizer.h"
#include "Math/Vector2.hpp"
#include "DerivativeTexcoord.h"

class RangeInt;
class Bounds;
namespace Renderer
{
	class Bresenham;
	class BresenhamList;
	class Vertex;
	class Triangle final : public IRasterizer
	{
	public:
		Triangle( const std::vector<Vertex>& vertices, const DerivativeTexcoord& derivatives );
		~Triangle() override;

		void Rasterize( const Bounds& bounds, ProcessPixel process );

	private:
		static bool AscendingY( const Vertex& left, const Vertex& right );
		static void Rasterize( const Bounds& bounds, BresenhamList& e1, BresenhamList& e2, ProcessPixel process, const DerivativeTexcoord& derivatives );

	private:
		const DerivativeTexcoord derivatives;
		const std::vector<Vertex> vertices;
		std::pair<size_t, size_t> minmax;
	};
}