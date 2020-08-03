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
		, ddx( Vector2::zero )
		, ddy( Vector2::zero )
		, values { 1.f, 0.f, Vector4::zero, Vector2::zero }
	{
	}

	RasterizedPixel::RasterizedPixel( const Vector2Int& coordinate, const PixelValues& values, const DerivativeTexcoord& derivatives )
		: isValid( true )
		, coordinate( coordinate )
		, ddx( derivatives.dFdx( values.texcoord, values.w ) )
		, ddy( derivatives.dFdy( values.texcoord, values.w ) )
		, values( values )
	{
	}

	RasterizedPixel::RasterizedPixel( const Vector2Int& coordinate, const PixelValues& values )
		: RasterizedPixel( coordinate, values, DerivativeTexcoord::invalid )
	{
	}

	RasterizedPixel::RasterizedPixel( const Bresenham& edge, const DerivativeTexcoord& derivatives )
		: RasterizedPixel( edge.p, edge.GetValues(), derivatives )
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
}