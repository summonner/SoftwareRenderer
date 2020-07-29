#pragma once
#include "IRasterizer.h"

class Bounds;
namespace Renderer
{
	class Vertex;
	class Point final : public IRasterizer
	{
	public:
		Point( const Vertex& v );
		~Point() override;

		void Rasterize( const Bounds& bounds, ProcessPixel process ) override;

	private:
		const Vertex& v;
	};
}