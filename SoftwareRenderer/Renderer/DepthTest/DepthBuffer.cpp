#pragma once
#include "framework.h"
#include "DepthBuffer.h"
#include "Math/Vector2.hpp"
#include "Math/Bounds.h"
#include "Renderer/Rasterizer/RasterizedPixel.h"
#include "Util/PixelIterator.h"

namespace Renderer 
{
	DepthBuffer::DepthBuffer( const Bounds& bounds )
		: DepthBuffer( bounds.x.Length(), bounds.y.Length() )
	{
	}

	DepthBuffer::DepthBuffer( int width, int height )
		: width( width )
		, height( height )
		, pixels( new float[width * height] )
		, clearValue( 1.f )
		, invalidate( false )
		, write( true )
	{
	}

	DepthBuffer::~DepthBuffer()
	{
	}

	void DepthBuffer::Reset()
	{
		BaseComponent::Reset();
		clearValue = 1.f;
		depthFunc = DepthFunc::Type::Less;
	}

	void DepthBuffer::Clear()
	{
		invalidate = true;
	}

	void DepthBuffer::Clear( const Bounds& bounds )
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

	void DepthBuffer::SetClearValue( const float value )
	{
		clearValue = value;
	}

	void DepthBuffer::SetDepthFunc( const DepthFunc::Type type )
	{
		depthFunc = type;
	}

	void DepthBuffer::SetWrite( bool enable )
	{
		write = enable;
	}

	float DepthBuffer::Get( const Vector2Int& coordinate ) const
	{
		auto p = ToIndex( coordinate );
		return (pixels[p] + 1) * 0.5f;
	}

	int DepthBuffer::ToIndex( const Vector2Int& coordinate ) const
	{
		return coordinate.y * width + coordinate.x;
	}

	bool DepthBuffer::Test( const RasterizedPixel& p ) const
	{
		if ( enabled == false )
		{
			return true;
		}

		return Test( p.coordinate, p.GetDepth() );
	}

	bool DepthBuffer::Test( const Vector2Int& coordinate, float depth ) const
	{
		auto p = ToIndex( coordinate );
		if ( depthFunc( depth, pixels[p] ) )
		{
			if ( write == true )
			{
				pixels[p] = depth;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
}