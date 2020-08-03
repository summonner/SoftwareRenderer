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

		virtual void PerspectiveDivide( const Matrix4x4& viewport ) abstract;

		using CullFunc = std::function<bool( const Vector2Int&, const Vector2Int&, const Vector2Int& )>;
		virtual bool CheckFacet( CullFunc cullFunc ) abstract;

		using ProcessPixel = std::function<void( const RasterizedPixel& )>;
		virtual void Rasterize( const Bounds& bounds, ProcessPixel process ) abstract;
	};
}