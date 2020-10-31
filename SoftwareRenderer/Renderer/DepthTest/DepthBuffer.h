#pragma once
#include "IDepthBufferController.h"

class Bounds;
namespace Renderer
{
	class RasterizedPixel;
	class DepthBuffer final : public IDepthBufferController
	{
	public:
		DepthBuffer( const Bounds& bounds );
		DepthBuffer( int width, int height );
		~DepthBuffer() override;

		void Reset() override;
		void Clear() override;
		void Clear( const Bounds& bounds );
		void SetClearValue( const float value ) override;
		void SetDepthFunc( const DepthFunc::Type type ) override;
		void SetWrite( bool enable ) override;
		float Get( const Vector2Int& coordinate ) const override;

		bool Test( const RasterizedPixel& p ) const;

	private:
		int ToIndex( const Vector2Int& coordinate ) const;
		bool Test( const Vector2Int& coordinate, float depth ) const;

	private:
		const int width;
		const int height;
		std::unique_ptr<float[]> pixels;
		float clearValue;
		bool invalidate;

		DepthFunc depthFunc;
		bool write;
	};
}