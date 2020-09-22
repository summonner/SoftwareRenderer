#include "framework.h"
#include "VertexInterpolator.h"
#include "Renderer/Vertex.h"
#include "../PixelValues.h"

namespace Renderer
{
	VertexInterpolator::VertexInterpolator( const Vertex& a, const Vertex& b, const ShadeModel::ShadeFunc shadeFunc )
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
			Lerp( a.position.w, b.position.w, t ),
			Lerp( a.position.z, b.position.z, t ),
			shadeFunc( t ),
			Vector2::Lerp( a.texcoord, b.texcoord, t ),
		};
	}
}