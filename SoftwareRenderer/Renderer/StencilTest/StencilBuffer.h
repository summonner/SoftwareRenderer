#pragma once
#include "IStencilBufferController.h"
#include "StencilFunc.h"
#include "StencilOp.h"

class Bounds;
namespace Renderer
{
	class RasterizedPixel;
	class StencilBuffer final : public IStencilBufferController
	{
	public:
		StencilBuffer( const Bounds& bounds );
		StencilBuffer( int width, int height );
		~StencilBuffer() override;

		void Reset() override;
		void Clear() override;
		void Clear( const Bounds& bounds );
		void SetClearValue( StencilValue value ) override;

		bool Test( const RasterizedPixel& p, std::function<bool()> depthTest );
		bool invalidate;


	private:
		StencilValue clearValue;
		std::unique_ptr<StencilValue[]> pixels;

		const int width;
		const int height;

	private:
		bool Test( const Vector2Int& p, std::function<bool()> depthTest, const Properties& face );

	};
}