#include "framework.h"
#include "Line.h"
#include "SutherlanHodgman.h"
#include "Renderer/Vertex.h"
#include "Renderer/Rasterizer/DerivativeTexcoord.h"
#include "Renderer/Rasterizer/LineRasterizer.h"

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

	std::unique_ptr<IRasterizer> Line::Clip() const
	{
		auto vertices = SutherlandHodgman::ClipLine( { a, b } );
		auto derivatives = [&]() { return Derivative(); };
		return std::make_unique<LineRasterizer>( std::move( vertices ), derivatives );
	}

	DerivativeTexcoord Line::Derivative() const
	{
		return DerivativeTexcoord::Line( a, b );
	}
}