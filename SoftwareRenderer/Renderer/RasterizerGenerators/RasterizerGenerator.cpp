#include "framework.h"
#include "RasterizerGenerator.h"
#include "PointGenerator.h"
#include "LineGenerator.h"
#include "TriangleGenerator.h"
#include "QuadGenerator.h"
#include "Renderer/Rasterizer/IRasterizer.h"

namespace Renderer
{
	std::map<IRenderer::DrawMode, const RasterizerGenerator::GeneratorFunction> RasterizerGenerator::table
	{
		{ IRenderer::DrawMode::Points,		PointGenerator::Default },
		{ IRenderer::DrawMode::Lines,		LineGenerator::Default },
		{ IRenderer::DrawMode::LineStrip,	LineGenerator::Strip },
		{ IRenderer::DrawMode::LineLoop,	LineGenerator::Loop },
		{ IRenderer::DrawMode::Triangles,	TriangleGenerator::Default },
		{ IRenderer::DrawMode::TriangleStrip, TriangleGenerator::Strip },
		{ IRenderer::DrawMode::TriangleFan, TriangleGenerator::Fan },
		{ IRenderer::DrawMode::Quads,		QuadGenerator::Quads },
	};

	RasterizerGenerator::RasterizerGenerator()
	{
	}

	RasterizerGenerator::~RasterizerGenerator()
	{
	}

	void RasterizerGenerator::Begin( IRenderer::DrawMode mode )
	{
		generator = FindGenerator( mode );
	}

	const RasterizerGenerator::GeneratorFunction RasterizerGenerator::FindGenerator( IRenderer::DrawMode mode )
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

	const IRasterizerList& RasterizerGenerator::Generate( const VertexBuffer& vertices )
	{
		if ( generator != nullptr )
		{
			generator( vertices, rasterizers );
		}

		return rasterizers;
	}

	void RasterizerGenerator::Flush()
	{
		rasterizers.clear();
	}
}