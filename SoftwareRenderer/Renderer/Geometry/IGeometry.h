#pragma once

class Matrix4x4;
namespace Renderer
{
	class IRasterizer;
	class PlaneIterator;
	class IGeometry abstract
	{
	public:
		virtual ~IGeometry() {}

		virtual std::unique_ptr<IRasterizer> Clip( const Matrix4x4& viewport, const PlaneIterator& planes ) const abstract;
	};
}