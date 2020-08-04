#include "framework.h"
#include "Line.h"
#include "SutherlanHodgman.h"
#include "Renderer/Vertex.h"
#include "Renderer/Rasterizer/DerivativeTexcoord.h"
#include "Renderer/Rasterizer/LineRasterizer.h"
#include "Renderer/Rasterizer/PointRasterizer.h"

namespace Renderer
{
	Line::Line( const Vertex& a, const Vertex& b )
		: a( a )
		, b( b )
	{
	}

	Line::~Line()
	{
	}

	std::unique_ptr<IRasterizer> Line::Clip( const Matrix4x4& viewport ) const
	{
		auto vertices = SutherlandHodgman::ClipLine( { a, b } );
		if ( vertices.size() <= 0 )
		{
			return nullptr;
		}

		assert( vertices.size() == 2 );
		for ( auto& v : vertices )
		{
			v.PerspectiveDivide( viewport );
		}

		if ( vertices[0].screen == vertices[1].screen )
		{
			return std::make_unique<PointRasterizer>( vertices[0] );
		}

		return std::make_unique<LineRasterizer>( std::move( vertices ) );
	}
}