#include "framework.h"
#include "Line.h"
#include "Renderer/Vertex.h"
#include "Renderer/Clipping/SutherlandHodgman.h"
#include "Renderer/Rasterizer/DerivativeTexcoord.h"
#include "Renderer/Rasterizer/LineRasterizer.h"
#include "Renderer/Rasterizer/PointRasterizer.h"
#include "Renderer/Rasterizer/ShadeModel.h"

namespace Renderer
{
	float Line::width = 1.f;
	bool Line::smooth = false;

	Line::Line( const Vertex& a, const Vertex& b )
		: a( a )
		, b( b )
	{
	}

	Line::~Line()
	{
	}

	std::unique_ptr<IRasterizer> Line::Clip( const Matrix4x4& viewport, const PlaneIterator& planes ) const
	{
		auto vertices = SutherlandHodgman::ClipLine( { a, b }, planes );
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
			return std::make_unique<PointRasterizer>( vertices[0], width, false );
		}

		return std::make_unique<LineRasterizer>( std::move( vertices ), ShadeModel::FlatFunc( b.color ) );
	}
}