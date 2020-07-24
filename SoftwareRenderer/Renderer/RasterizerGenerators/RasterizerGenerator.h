#pragma once
#include "Renderer/IRenderer.h"
#include "Types.h"
#include "Util/Dictionary.hpp"

namespace Renderer
{
	class RasterizerGenerator final
	{
	public:
		RasterizerGenerator();
		~RasterizerGenerator();

		void Begin( IRenderer::DrawMode mode );
		const IRasterizerList& Generate( const VertexBuffer& vertices );
		void Flush();

	private:
		using GeneratorFunction = std::function<void( const std::vector<Vertex>&, IRasterizerList& )>;
		static const Dictionary<IRenderer::DrawMode, const GeneratorFunction> table;

		GeneratorFunction generator;
		IRasterizerList rasterizers;
	};

}