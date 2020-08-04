#pragma once

class Bounds;
class Matrix4x4;
namespace Renderer
{
	class RasterizedPixel;
	class DerivativeTexcoord;
	class IRasterizer abstract
	{
	public:
		virtual ~IRasterizer() {}

		virtual float CheckFacet() const abstract;

		virtual DerivativeTexcoord Derivative( const bool isTextureEnabled ) const abstract;

		using ProcessPixel = std::function<void( const RasterizedPixel& )>;
		virtual void Rasterize( const Bounds& bounds, const ProcessPixel process ) abstract;
	};
}