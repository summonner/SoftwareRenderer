#include "framework.h"
#include "CommonRasterizer.h"
#include "DerivativeTexcoord.h"
#include "Renderer/Vertex.h"
#include "RasterizedPixel.h"

namespace Renderer
{
	CommonRasterizer::CommonRasterizer( std::vector<Vertex>&& vertices )
		: vertices( std::move( vertices ) )
	{
		assert( this->vertices.size() > 2 );
	}

	CommonRasterizer::~CommonRasterizer()
	{
	}

	void CommonRasterizer::PerspectiveDivide( const Matrix4x4& viewport )
	{
		for ( auto& v : vertices )
		{
			v.PerspectiveDivide( viewport );
		}
	}

	bool CommonRasterizer::CheckFacet( CullFunc cullFunc )
	{
		auto ignore = cullFunc == nullptr
				   || vertices.size() < 3;
		if ( ignore )
		{
			return true;
		}

		return cullFunc( vertices[0].screen, vertices[1].screen, vertices[2].screen );
	}

	void CommonRasterizer::Rasterize( const Bounds& bounds, ProcessPixel process )
	{
		const auto derivatives = Derivative();
		if ( derivatives.IsValid() == false )
		{
			process( RasterizedPixel( vertices[0] ) );
			return;
		}

		Rasterize( bounds, process, derivatives );
	}

	DerivativeTexcoord CommonRasterizer::Derivative() const
	{
		const auto numVertices = vertices.size();
		if ( numVertices < 2 )
		{
			return DerivativeTexcoord::invalid;
		}
		else if ( numVertices == 2 )
		{
			return DerivativeTexcoord::Line( vertices[0], vertices[1] );
		}
		else // numVertices > 2
		{
			return DerivativeTexcoord::Triangle( vertices[0], vertices[1], vertices[2] );
		}
	}
}