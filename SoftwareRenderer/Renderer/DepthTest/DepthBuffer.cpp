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
		, pixels( nullptr )
		, clearValue( 1.f )
	{
	}

	DepthBuffer::~DepthBuffer()
	{
	}

	void DepthBuffer::SetEnable( bool enable )
	{
		if ( enable == true && pixels == nullptr )
		{
			pixels = std::make_unique<float[]>( width * height );
		}
		else if ( enable == false )
		{
			pixels = nullptr;
		}
	}

	void DepthBuffer::Clear()
	{
		if ( pixels == nullptr )
		{
			return;
		}

		std::fill( pixels.get(), pixels.get() + width * height, clearValue );
	}

	void DepthBuffer::SetClearValue( const float value )
	{
		if ( pixels == nullptr )
		{
			return;
		}

		clearValue = value;
	}

	void DepthBuffer::SetDepthFunc( const DepthFunc::Type type )
	{
		if ( pixels == nullptr )
		{
			return;
		}

		depthFunc = type;
	}

	bool DepthBuffer::Test( const RasterizedPixel& p ) const
	{
		if ( pixels == nullptr )
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