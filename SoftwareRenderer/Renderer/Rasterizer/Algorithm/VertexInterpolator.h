#pragma once
#include "../PixelValues.h"
#include "../ShadeModel.h"

namespace Renderer
{
	class Vertex;
	class VertexInterpolator final
	{
	public:
		VertexInterpolator( const Vertex& a, const Vertex& b, ShadeModel::ShadeFunc shadeFunc );
		VertexInterpolator( const PixelValues& a, const PixelValues& b, ShadeModel::ShadeFunc shadeFunc );
		~VertexInterpolator();

		PixelValues Get( float t ) const;
		static PixelValues ExtractValues( const Vertex& v );

	private:
		const PixelValues a;
		const PixelValues b;

		const ShadeModel::ShadeFunc shadeFunc;
	};
}