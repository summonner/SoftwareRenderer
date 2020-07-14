#include "framework.h"
#include "PrimitiveGenerator.h"
#include "PointGenerator.h"
#include "LineGenerator.h"
#include "TriangleGenerator.h"

namespace Renderer
{

	std::map<IRenderer::DrawMode, const PrimitiveGenerator::GeneratorFunction> PrimitiveGenerator::table
	{
		{ IRenderer::DrawMode::Points,		PointGenerator::Default },
		{ IRenderer::DrawMode::Lines,		LineGenerator::Default },
		{ IRenderer::DrawMode::LineStrip,	LineGenerator::Strip },
		{ IRenderer::DrawMode::LineLoop,	LineGenerator::Loop },
		{ IRenderer::DrawMode::Triangles,	TriangleGenerator::Triangles },
		{ IRenderer::DrawMode::TriangleStrip, TriangleGenerator::TriangleStrip },
		{ IRenderer::DrawMode::TriangleFan, TriangleGenerator::TriangleFan },
	};

	PrimitiveGenerator::PrimitiveGenerator()
	{
	}

	PrimitiveGenerator::~PrimitiveGenerator()
	{
	}

	void PrimitiveGenerator::SetMode( IRenderer::DrawMode mode, int startIndex )
	{
		this->startIndex = startIndex;
		generator = FindGenerator( mode );
	}

	const PrimitiveGenerator::GeneratorFunction PrimitiveGenerator::FindGenerator( IRenderer::DrawMode mode )
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

	void PrimitiveGenerator::Generate( const VertexBuffer& vertices, IPrimitiveList& outPrimitives )
	{
		if ( generator == nullptr )
		{
			return;
		}

		generator( vertices, startIndex, outPrimitives );
		generator = nullptr;
	}
}