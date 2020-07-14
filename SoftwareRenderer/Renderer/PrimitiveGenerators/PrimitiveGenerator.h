#pragma once
#include "Renderer/IRenderer.h"
#include "Types.h"

namespace Renderer
{
	class PrimitiveGenerator final
	{
	public:
		PrimitiveGenerator();
		~PrimitiveGenerator();

		void SetMode( IRenderer::DrawMode mode, int startIndex );
		void Generate( const VertexBuffer& vertices, IPrimitiveList& primitives );

	private:
		using GeneratorFunction = std::function<void( const std::vector<Vertex>&, int, IPrimitiveList& )>;
		static std::map<IRenderer::DrawMode, const GeneratorFunction> table;
		static const GeneratorFunction FindGenerator( IRenderer::DrawMode mode );

		GeneratorFunction generator;
		int startIndex;
	};

}