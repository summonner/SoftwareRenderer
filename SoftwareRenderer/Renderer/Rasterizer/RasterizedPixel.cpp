#include "framework.h"
#include "RasterizedPixel.h"
#include "Algorithm/Bresenham.h"
#include "DerivativeTexcoord.h"
#include "Renderer/Vertex.h"
#include "ShadeModel.h"

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

	RasterizedPixel::RasterizedPixel( int x, int y, const PixelValues& values )
		: RasterizedPixel( Vector2Int( x, y ), values )
	{
	}

	RasterizedPixel RasterizedPixel::AdditionalAlpha( const Vector2Int& p, PixelValues values, float alpha )
	{
		values.color.w *= alpha;
		return RasterizedPixel( p.x, p.y, values );
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
		if ( ShadeModel::IsFlat() == true )
		{
			return values.color;
		}
		else
		{
			return values.color / values.w;
		}
	}

	Vector2 RasterizedPixel::GetTexcoord() const
	{
		return values.texcoord / values.w;
	}

	float RasterizedPixel::GetEyeDepth() const
	{
		return values.depth / values.w;
	}

	const PixelValues& RasterizedPixel::GetRawValues() const
	{
		return values;
	}
}