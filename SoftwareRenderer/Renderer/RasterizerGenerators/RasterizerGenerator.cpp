#include "framework.h"
#include "RasterizerGenerator.h"
#include "PointGenerator.h"
#include "LineGenerator.h"
#include "TriangleGenerator.h"
#include "QuadGenerator.h"

namespace Renderer
{

	std::map<IRenderer::DrawMode, const RasterizerGenerator::GeneratorFunction> RasterizerGenerator::table
	{
		{ IRenderer::DrawMode::Points,		PointGenerator::Default },
		{ IRenderer::DrawMode::Lines,		LineGenerator::Default },
		{ IRenderer::DrawMode::LineStrip,	LineGenerator::Strip },
		{ IRenderer::DrawMode::LineLoop,	LineGenerator::Loop },
		{ IRenderer::DrawMode::Triangles,	TriangleGenerator::Triangles },
		{ IRenderer::DrawMode::TriangleStrip, TriangleGenerator::TriangleStrip },
		{ IRenderer::DrawMode::TriangleFan, TriangleGenerator::TriangleFan },
		{ IRenderer::DrawMode::Quads,		QuadGenerator::Quads },
	};

	RasterizerGenerator::RasterizerGenerator()
	{
	}

	RasterizerGenerator::~RasterizerGenerator()
	{
	}

	void RasterizerGenerator::Begin( IRenderer::DrawMode mode, int startIndex )
	{
		temp.start = startIndex;
		temp.generator = FindGenerator( mode );
	}

	void RasterizerGenerator::End( int endIndex )
	{
		temp.end = endIndex;
		generators.push( temp );
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

	void RasterizerGenerator::Generate( const VertexBuffer& vertices, IRasterizerList& outRasterizers )
	{
		while ( generators.size() > 0 )
		{
			auto generator = generators.front();
			generator.Generate( vertices, outRasterizers );
			generators.pop();
		}
	}

	void RasterizerGenerator::Generator::Generate( const VertexBuffer& vertices, IRasterizerList& outRasterizers )
	{
		generator( vertices, start, end, outRasterizers );
	}
}