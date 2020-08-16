#pragma once
#include "IGeometry.h"

namespace Renderer
{
	class Vertex;
	class DerivativeTexcoord;
	class Line final : public IGeometry
	{
	public:
		Line( const Vertex& a, const Vertex& b );
		~Line() override;

		std::unique_ptr<IRasterizer> Clip( const Matrix4x4& viewport, const PlaneIterator& planes ) const;

	private:
		const Vertex& a;
		const Vertex& b;
	};
}