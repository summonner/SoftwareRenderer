#pragma once
#include "framework.h"
#include "DepthBuffer.h"
#include "Math/Vector2.hpp"
#include "Renderer/Rasterizer/RasterizedPixel.h"

namespace Renderer 
{
	DepthBuffer::DepthBuffer( int width, int height )
		: width( width )
		, height( height )
		, pixels( new float[width * height] )
		, clearValue( 1.f )
		, enabled( false )
	{
	}

	DepthBuffer::~DepthBuffer()
	{
	}

	void DepthBuffer::SetEnable( bool enable )
	{
		enabled = enable;
	}

	void DepthBuffer::Clear()
	{
		std::fill( pixels.get(), pixels.get() + width * height, clearValue );
	}

	void DepthBuffer::SetClearValue( const float value )
	{
		clearValue = value;
	}

	void DepthBuffer::SetDepthFunc( const DepthFunc::Type type )
	{
		depthFunc = type;
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
		auto p = coordinate.y * width + coordinate.x;
		if ( depthFunc( depth, pixels[p] ) )
		{
			pixels[p] = depth;
			return true;
		}
		else
		{
			return false;
		}
	}
}