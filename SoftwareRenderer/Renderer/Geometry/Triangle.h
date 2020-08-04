#pragma once
#include "IGeometry.h"

namespace Renderer
{
	class Vertex;
	class DerivativeTexcoord;
	class Triangle final : public IGeometry
	{
	public:
		Triangle( const Vertex& a, const Vertex& b, const Vertex& c );
		~Triangle() override;

		std::unique_ptr<IRasterizer> Clip( const Matrix4x4& viewport ) const override;

	private:
		static int SelectSecondVertex( const std::vector<Vertex>& vertices );
		static int SelectThirdVertex( const std::vector<Vertex>& vertices, size_t secondIndex );

	private:
		const Vertex& a;
		const Vertex& b;
		const Vertex& c;
	};
}