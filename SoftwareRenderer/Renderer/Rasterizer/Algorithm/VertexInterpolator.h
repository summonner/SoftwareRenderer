#pragma once
#include "../ShadeModel.h"

namespace Renderer
{
	class Vertex;
	struct PixelValues;
	class VertexInterpolator final
	{
	public:
		VertexInterpolator( const Vertex& a, const Vertex& b, ShadeModel::ShadeFunc shadeFunc );
		~VertexInterpolator();

		PixelValues Get( float t ) const;

	private:
		const Vertex& a;
		const Vertex& b;

		const ShadeModel::ShadeFunc shadeFunc;
	};
}