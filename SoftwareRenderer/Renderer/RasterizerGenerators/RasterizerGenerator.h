#pragma once
#include "Renderer/IRenderer.h"
#include "Types.h"

namespace Renderer
{
	class RasterizerGenerator final
	{
	public:
		RasterizerGenerator();
		~RasterizerGenerator();

		void Begin( IRenderer::DrawMode mode );
		void Generate( const VertexBuffer& vertices, IRasterizerList& primitives );

	private:
		using GeneratorFunction = std::function<void( const std::vector<Vertex>&, IRasterizerList& )>;
		static std::map<IRenderer::DrawMode, const GeneratorFunction> table;
		static const GeneratorFunction FindGenerator( IRenderer::DrawMode mode );

		GeneratorFunction generator;
	};

}