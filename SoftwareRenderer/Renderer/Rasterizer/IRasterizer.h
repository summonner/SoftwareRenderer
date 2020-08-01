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
		virtual void Rasterize( const Matrix4x4& viewport, const Bounds& bounds, ProcessPixel process ) abstract;
	};
}