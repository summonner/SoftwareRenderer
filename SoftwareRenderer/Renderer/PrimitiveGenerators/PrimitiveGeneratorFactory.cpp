#include "framework.h"
#include "PrimitiveGeneratorFactory.h"
#include "PointGenerator.h"
#include "LineGenerator.h"
#include "Renderer/Primitives/IPrimitive.h"
#include "Renderer/Primitives/Triangle.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	IPrimitiveList Triangles( VertexBuffer vertices );
	IPrimitiveList TriangleStrip( VertexBuffer vertices );
	IPrimitiveList TriangleFan( VertexBuffer vertices );

	std::map<IRenderer::DrawMode, PrimitiveGeneratorFactory::GeneratorFunction> PrimitiveGeneratorFactory::table
	{
		{ IRenderer::DrawMode::Points,		PointGenerator::Default },
		{ IRenderer::DrawMode::Lines,		LineGenerator::Default },
		{ IRenderer::DrawMode::LineStrip,	LineGenerator::Strip },
		{ IRenderer::DrawMode::LineLoop,	LineGenerator::Loop },
		{ IRenderer::DrawMode::Triangles,	Triangles },
		{ IRenderer::DrawMode::TriangleStrip, TriangleStrip },
		{ IRenderer::DrawMode::TriangleFan, TriangleFan },
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

	IPrimitiveList Triangles( VertexBuffer vertices )
	{
		IPrimitiveList primitives;
		auto numVertices = vertices.size() - 2;
		for ( auto i = 0; i < numVertices; i += 3 )
		{
			primitives.push_back( std::make_unique<Triangle>( vertices[i], vertices[i + 1], vertices[i + 2] ) );
		}

		return primitives;
	}

	IPrimitiveList TriangleStrip( VertexBuffer vertices )
	{
		IPrimitiveList primitives;
		auto numVertices = vertices.size() - 3;
		for ( auto i = 0; i < numVertices; i += 2 )
		{
			primitives.push_back( std::make_unique<Triangle>( vertices[i], vertices[i + 1], vertices[i + 2] ) );
			primitives.push_back( std::make_unique<Triangle>( vertices[i + 2], vertices[i + 1], vertices[i + 3] ) );
		}

		return primitives;
	}

	IPrimitiveList TriangleFan( VertexBuffer vertices )
	{
		IPrimitiveList primitives;
		auto numVertices = vertices.size() - 2;
		for ( auto i = 1; i < numVertices; i += 1 )
		{
			primitives.push_back( std::make_unique<Triangle>( vertices[0], vertices[i], vertices[i + 1] ) );
		}

		return primitives;
	}
}