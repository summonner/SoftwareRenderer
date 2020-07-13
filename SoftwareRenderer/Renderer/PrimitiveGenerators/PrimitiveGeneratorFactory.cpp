#include "framework.h"
#include "PrimitiveGeneratorFactory.h"
#include "PointGenerator.h"
#include "LineGenerator.h"
#include "Renderer/Primitives/IPrimitive.h"

namespace Renderer
{
	std::map<IRenderer::DrawMode, PrimitiveGeneratorFactory::GeneratorFunction> PrimitiveGeneratorFactory::table
	{
		{ IRenderer::DrawMode::Points,		PointGenerator::Default },
		{ IRenderer::DrawMode::Lines,		LineGenerator::Default },
		{ IRenderer::DrawMode::LineStrip,	LineGenerator::Strip },
		{ IRenderer::DrawMode::LineLoop,	LineGenerator::Loop },
	};

	PrimitiveGeneratorFactory::PrimitiveGeneratorFactory()
	{
	}

	PrimitiveGeneratorFactory::~PrimitiveGeneratorFactory()
	{
	}

	PrimitiveGeneratorFactory::GeneratorFunction PrimitiveGeneratorFactory::Create( IRenderer::DrawMode mode ) const
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