#pragma once
#include "IRasterizer.h"

class RangeInt;
class Bounds;
namespace Renderer
{
	class Bresenham;
	class BresenhamList;
	class Vertex;
	class DerivativeTexcoord;
	class Triangle final : public IRasterizer
	{
	public:
		Triangle( const Vertex& a, const Vertex& b, const Vertex& c );
		~Triangle() override;

		std::unique_ptr<IRasterizer> Clip() const override;
	private:
		DerivativeTexcoord Derivative() const;

	private:
		const Vertex& a;
		const Vertex& b;
		const Vertex& c;
	};
}