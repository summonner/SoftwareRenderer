#include "framework.h"
#include "Triangle.h"
#include "SutherlanHodgman.h"
#include "Renderer/Vertex.h"
#include "Renderer/Rasterizer/PointRasterizer.h"
#include "Renderer/Rasterizer/LineRasterizer.h"
#include "Renderer/Rasterizer/PolygonRasterizer.h"

namespace Renderer
{
	Triangle::Triangle( const Vertex& a, const Vertex& b, const Vertex& c )
		: a( a )
		, b( b )
		, c( c )
	{
	}

	Triangle::~Triangle()
	{
	}

	std::unique_ptr<IRasterizer> Triangle::Clip( const Matrix4x4& viewport ) const
	{
		auto vertices = SutherlandHodgman::ClipPolygon( { a, b, c } );
		if ( vertices.size() < 3 )
		{
			return nullptr;
		}

		for ( auto& v : vertices )
		{
			v.PerspectiveDivide( viewport );
		}

		const int secondIndex = SelectSecondVertex( vertices );
		if ( secondIndex < 0 )
		{
			return std::make_unique<PointRasterizer>( vertices[0] );
		}

		const int thirdIndex = SelectThirdVertex( vertices, secondIndex );
		if ( thirdIndex < 0 )
		{

			return std::make_unique<LineRasterizer>( vertices[0], vertices[secondIndex] );
		}

		return std::make_unique<PolygonRasterizer>( std::move( vertices ), secondIndex, thirdIndex );
	}

	int Triangle::SelectSecondVertex( const std::vector<Vertex>& vertices )
	{
		for ( auto i = 0u; i < vertices.size(); ++i )
		{
			if ( vertices[i].screen != vertices[0].screen )
			{
				return i;
			}
		}

		return -1;
	}

	int Triangle::SelectThirdVertex( const std::vector<Vertex>& vertices, size_t secondIndex )
	{
		const auto ab = vertices[secondIndex].screen - vertices[0].screen;
		for ( auto i = secondIndex + 1; i < vertices.size(); ++i )
		{
			const auto ac = vertices[i].screen - vertices[0].screen;
			if ( ab.Area( ac ) != 0 )
			{
				return i;
			}
		}

		return -1;
	}
}