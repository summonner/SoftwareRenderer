#pragma once
#include "DepthFunc.h"
#include "Renderer/IComponent.h"

namespace Renderer
{
	class RasterizedPixel;
	class DepthBuffer final : public BaseComponent
	{
	public:
		DepthBuffer( int width, int height );
		~DepthBuffer();

		void Reset() override;
		void Clear();
		void SetClearValue( const float value );
		void SetDepthFunc( const DepthFunc::Type type );

		bool Test( const RasterizedPixel& p ) const;

	private:
		bool Test( const Vector2Int& coordinate, float depth ) const;

	private:
		const int width;
		const int height;
		std::unique_ptr<float[]> pixels;
		float clearValue;

		DepthFunc depthFunc;
	};
}