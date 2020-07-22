#pragma once
#include "framework.h"
#include "DepthBuffer.h"
#include "Math/Vector2.hpp"

namespace Renderer 
{
	DepthBuffer::DepthBuffer( int width, int height )
		: width( width )
		, height( height )
		, pixels( new float[ width * height ] )
	{
	}

	DepthBuffer::~DepthBuffer()
	{
	}

	void DepthBuffer::Clear()
	{
		memset( pixels.get(), 0, sizeof( float ) * width * height );
	}

	bool DepthBuffer::Test( const Vector2Int& coordinate, float depth )
	{
		auto p = coordinate.y * width + coordinate.x;
		depth -= 1.f;
		if ( depth <= pixels[p] && depth >= -2.f )
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