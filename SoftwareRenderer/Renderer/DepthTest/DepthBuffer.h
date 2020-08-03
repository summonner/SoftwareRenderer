#pragma once
#include "DepthFunc.h"

namespace Renderer
{
	class RasterizedPixel;
	class DepthBuffer final
	{
	public:
		DepthBuffer( int width, int height );
		~DepthBuffer();

		void SetEnable( bool enable );

		void Clear();
		void SetClearValue( const float value );
		void SetDepthFunc( const DepthFunc::Type type );

		bool Test( const RasterizedPixel& p ) const;

	private:
		bool Test( const Vector2Int& coordinate, float depth ) const;

	private:
		bool enabled;
		const int width;
		const int height;
		std::unique_ptr<float[]> pixels;
		float clearValue;

		DepthFunc depthFunc;
	};
}