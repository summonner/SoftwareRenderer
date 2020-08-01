#pragma once

class Bounds;
class Matrix4x4;
namespace Renderer
{
	class RasterizedPixel;
	class IRasterizer abstract
	{
	public:
		virtual ~IRasterizer() {}

		using ProcessPixel = std::function<void( const RasterizedPixel& )>;
		virtual void Rasterize( const Bounds& bounds, ProcessPixel process )
		{
		}

		virtual void Rasterize( const Matrix4x4& viewport, const Bounds& bounds, ProcessPixel process )
		{
			Rasterize( bounds, process );
		}

		virtual std::unique_ptr<IRasterizer> Clip() const { return nullptr; };
	};
}