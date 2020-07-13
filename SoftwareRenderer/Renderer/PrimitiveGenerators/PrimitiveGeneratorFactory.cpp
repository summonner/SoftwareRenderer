#include "framework.h"
#include "PrimitiveGeneratorFactory.h"
#include "PointGenerator.h"

namespace Renderer
{
	std::map<IRenderer::DrawMode, const std::shared_ptr<IPrimitiveGenerator>> PrimitiveGeneratorFactory::table
	{
		{ IRenderer::DrawMode::Points, std::make_shared<PointGenerator>() },
	};

	PrimitiveGeneratorFactory::PrimitiveGeneratorFactory()
	{
	}

	PrimitiveGeneratorFactory::~PrimitiveGeneratorFactory()
	{
	}

	std::shared_ptr<IPrimitiveGenerator> PrimitiveGeneratorFactory::Create( IRenderer::DrawMode mode ) const
	{
		if ( const auto& found { table.find( mode ) }; found != table.end() )
		{
			return found->second;
		}
		else
		{
			return nullptr;
		}
	}
}