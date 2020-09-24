#include "framework.h"
#include "VertexInterpolator.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	VertexInterpolator::VertexInterpolator( const Vertex& a, const Vertex& b, const ShadeModel::ShadeFunc shadeFunc )
		: VertexInterpolator( ExtractValues( a ), ExtractValues( b ), shadeFunc )
	{
	}

	VertexInterpolator::VertexInterpolator( const PixelValues& a, const PixelValues& b, const ShadeModel::ShadeFunc shadeFunc )
		: a( a )
		, b( b )
		, shadeFunc( shadeFunc != nullptr ? shadeFunc : ShadeModel::SmoothFunc( a.color, b.color ) )
	{
	}

	VertexInterpolator::~VertexInterpolator()
	{
	}

	PixelValues VertexInterpolator::Get( float t ) const
	{
		return PixelValues
		{
			Lerp( a.w, b.w, t ),
			Lerp( a.depth, b.depth, t ),
			shadeFunc( t ),
			Vector2::Lerp( a.texcoord, b.texcoord, t ),
		};
	}

	PixelValues VertexInterpolator::ExtractValues( const Vertex& v )
	{
		return PixelValues
		{
			v.position.w,
			v.position.z,
			v.color,
			v.texcoord,
		};
	}
}