#pragma once
#include "Renderer/IRenderer.h"
#include "IPrimitiveGenerator.h"

namespace Renderer
{
	class PrimitiveGeneratorFactory final
	{
	public:
		PrimitiveGeneratorFactory();
		~PrimitiveGeneratorFactory();

		using GeneratorFunction = const std::function<IPrimitiveList( const std::vector<Vertex>& )>;
		GeneratorFunction Create( IRenderer::DrawMode mode ) const;

	private:
		static std::map<IRenderer::DrawMode, GeneratorFunction> table;
	};

}