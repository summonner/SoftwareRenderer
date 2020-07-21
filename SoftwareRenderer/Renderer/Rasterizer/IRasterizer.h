#pragma once

class Bounds;
namespace Renderer
{
	class RasterizedPixel;
	class IRasterizer abstract
	{
	public:
		virtual ~IRasterizer() {}

		using ProcessPixel = std::function<void( const RasterizedPixel& )>;
		virtual void Rasterize( const Bounds& bounds, ProcessPixel process ) const abstract;
	};
}