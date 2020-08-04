#include "framework.h"
#include "RasterizedPixel.h"
#include "Bresenham.h"
#include "DerivativeTexcoord.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	RasterizedPixel::RasterizedPixel()
		: isValid( false )
		, coordinate( 0, 0 )
		, values { 1.f, 0.f, Vector4::zero, Vector2::zero }
	{
	}

	RasterizedPixel::RasterizedPixel( const Vector2Int& coordinate, const PixelValues& values )
		: isValid( true )
		, coordinate( coordinate )
		, values( values )
	{
	}

	RasterizedPixel::RasterizedPixel( const Bresenham& edge )
		: RasterizedPixel( edge.p, edge.GetValues() )
	{
	}

	RasterizedPixel::RasterizedPixel( const Vertex& vertex )
		: RasterizedPixel( vertex.screen, PixelValues { vertex.position.w, vertex.position.z, vertex.color, vertex.texcoord } )
	{
	}

	RasterizedPixel::~RasterizedPixel()
	{
	}

	const RasterizedPixel RasterizedPixel::discard = RasterizedPixel();

	Vector4 RasterizedPixel::GetColor() const
	{
		return values.color / values.w;
	}

	Vector2 RasterizedPixel::GetTexcoord() const
	{
		return values.texcoord / values.w;
	}

	const PixelValues& RasterizedPixel::GetRawValues() const
	{
		return values;
	}
}