#include "framework.h"
#include "StencilBuffer.h"
#include "Math/Bounds.h"
#include "Renderer/Rasterizer/RasterizedPixel.h"
#include "Util/PixelIterator.h"

namespace Renderer
{
	StencilBuffer::StencilBuffer( const Bounds& bounds )
		: StencilBuffer( bounds.x.max, bounds.y.max )
	{
	}

	StencilBuffer::StencilBuffer( int width, int height )
		: clearValue( 0 )
		, pixels( std::make_unique<StencilValue[]>( width* height ) )
		, width( width )
		, height( height )
		, invalidate( false )
	{
	}

	StencilBuffer::~StencilBuffer()
	{
	}

	void StencilBuffer::Reset()
	{
		clearValue = 0;
	}

	void StencilBuffer::Clear()
	{
		invalidate = true;
	}

	void StencilBuffer::Clear( const Bounds& bounds )
	{
		if ( invalidate == false )
		{
			return;
		}

		for ( auto p : bounds )
		{
			const auto i = p.x + p.y * width;
			pixels[i] = clearValue;
		}

		invalidate = false;
	}

	void StencilBuffer::SetClearValue( StencilValue value )
	{
		clearValue = value;
	}

	bool StencilBuffer::Test( const RasterizedPixel& p, std::function<bool()> depthTest )
	{
		return Test( p.coordinate, depthTest, front );
	}

	bool StencilBuffer::Test( const Vector2Int& p, std::function<bool()> depthTest, const Properties& face )
	{
		if ( IsEnable() == false )
		{
			return depthTest();
		}

		const int i = p.x + p.y * width;
		const int current = pixels[i];
		if ( face.Test( current ) == false )
		{
			pixels[i] = face.Write( face.fail, current );
			return false;
		}

		if ( depthTest() == false )
		{
			pixels[i] = face.Write( face.depthFail, current );
			return false;
		}

		pixels[i] = face.Write( face.pass, current );
		return true;
	}
}