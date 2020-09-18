#include "framework.h"
#include "GeometryGenerator.h"
#include "PointGenerator.h"
#include "LineGenerator.h"
#include "TriangleGenerator.h"
#include "QuadGenerator.h"
#include "Renderer/Geometry/IGeometry.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	const Dictionary<Mesh::DrawMode, const GeometryGenerator::GeneratorFunction> GeometryGenerator::table
	{
		{ Mesh::DrawMode::Points,		PointGenerator::Default },
		{ Mesh::DrawMode::Lines,		LineGenerator::Default },
		{ Mesh::DrawMode::LineStrip,	LineGenerator::Strip },
		{ Mesh::DrawMode::LineLoop,		LineGenerator::Loop },
		{ Mesh::DrawMode::Triangles,	TriangleGenerator::Default },
		{ Mesh::DrawMode::TriangleStrip, TriangleGenerator::Strip },
		{ Mesh::DrawMode::TriangleFan,	TriangleGenerator::Fan },
		{ Mesh::DrawMode::Quads,		QuadGenerator::Quads },
	};

	GeometryGenerator::GeometryGenerator()
	{
	}

	GeometryGenerator::~GeometryGenerator()
	{
	}

	void GeometryGenerator::Begin( Mesh::DrawMode mode )
	{
		generator = table[mode];
	}

	IGeometryList GeometryGenerator::Generate( const VertexBuffer& vertices )
	{
		IGeometryList geometries;
		if ( generator != nullptr && vertices.size() > 0 )
		{
			generator( vertices, geometries );
		}

		return geometries;
	}
}