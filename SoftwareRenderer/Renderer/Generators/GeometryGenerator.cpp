#include "framework.h"
#include "GeometryGenerator.h"
#include "PointGenerator.h"
#include "LineGenerator.h"
#include "TriangleGenerator.h"
#include "QuadGenerator.h"
#include "Renderer/Geometry/IGeometry.h"

namespace Renderer
{
	const Dictionary<IRenderer::DrawMode, const GeometryGenerator::GeneratorFunction> GeometryGenerator::table
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

	GeometryGenerator::GeometryGenerator()
	{
	}

	GeometryGenerator::~GeometryGenerator()
	{
	}

	void GeometryGenerator::Begin( IRenderer::DrawMode mode )
	{
		generator = table[mode];
	}

	IGeometryList GeometryGenerator::Generate( const VertexBuffer& vertices )
	{
		IGeometryList geometries;
		if ( generator != nullptr )
		{
			generator( vertices, geometries );
		}

		return geometries;
	}
}