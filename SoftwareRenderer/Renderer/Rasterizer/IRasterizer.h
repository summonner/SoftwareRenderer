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

		virtual bool PerspectiveDivide( const Matrix4x4& viewport ) abstract;

		using CullFunc = std::function<bool( const Vector2Int&, const Vector2Int&, const Vector2Int& )>;
		virtual bool CheckFacet( const CullFunc cullFunc ) const abstract;

		virtual DerivativeTexcoord Derivative( const bool isTextureEnabled ) const abstract;

		using ProcessPixel = std::function<void( const RasterizedPixel& )>;
		virtual void Rasterize( const Bounds& bounds, const ProcessPixel process ) abstract;
	};
}