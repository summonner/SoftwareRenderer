#pragma once
#include "Renderer/IRenderer.h"

namespace Renderer
{
	class IPrimitiveGenerator;
	class PrimitiveGeneratorFactory final
	{
	public:
		PrimitiveGeneratorFactory();
		~PrimitiveGeneratorFactory();

		std::shared_ptr<IPrimitiveGenerator> Create( IRenderer::DrawMode mode ) const;

	private:
		static std::map<IRenderer::DrawMode, const std::shared_ptr<IPrimitiveGenerator>> table;
	};

}