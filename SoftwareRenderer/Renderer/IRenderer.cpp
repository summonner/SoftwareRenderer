#include "framework.h"
#include "IRenderer.h"
#include "Geometry/IGeometry.h"
#include "Rasterizer/IRasterizer.h"
#include "Rasterizer/RasterizedPixel.h"
#include "Rasterizer/DerivativeTexcoord.h"
#include "Math/Bounds.h"
using namespace Renderer;

IRenderer::IRenderer( std::unique_ptr<IFrameBuffer> frameBuffer )
	: backBuffer( std::move( frameBuffer ) )
	, depthBuffer( backBuffer->GetBounds() )
{
}
	
IRenderer::~IRenderer()
{
}

void IRenderer::Render()
{
	for ( auto& vertex : vertices )
	{
		vertex.color *= lighting.GetColor( vertex.position, vertex.normal );
		vertex.Process( projection );
	}

	auto geometries = generator.Generate( vertices );
	for ( const auto& geometry : geometries )
	{
		auto rasterizer = geometry->Clip( viewport );
		if ( rasterizer == nullptr )
		{
			continue;
		}

		if ( cullFace.Apply( *rasterizer ) == false )
		{
			continue;
		}

		const auto derivatives = rasterizer->Derivative( texture.IsEnable() );
		rasterizer->Rasterize( backBuffer->GetBounds(), [&]( const RasterizedPixel& p )
		{
			if ( depthBuffer.Test( p ) == false )
			{
				return;
			}

			Vector4 color = p.GetColor();
			color *= texture.GetColor( p, derivatives );

			backBuffer->SetPixel( p.coordinate, color, blender.AsFunc() );
		} );
	}

	vertices.clear();
}

void IRenderer::Draw( const Mesh& mesh )
{
	generator.Begin( mesh.drawMode );
	vertices.reserve( mesh.size() );
	std::transform( mesh.begin(), mesh.end(), std::back_inserter( vertices ),
		[this]( const Vertex& v ) { return TransformVertex( v ); } );
	Render();
}

Vertex IRenderer::TransformVertex( Vertex v ) const
{
	v.position = modelView * v.position;
	v.normal = Vector4( v.normal, 0 ) * modelView.Inverse();
	return v;
}

void IRenderer::Reset()
{
	backBuffer->Reset();

	depthBuffer.Reset();
	texture.Reset();
	cullFace.Reset();
	lighting.Reset();
	blender.Reset();
	Renderer::ShadeModel::type = Renderer::ShadeModel::Type::Smooth;

	modelView.Reset();
	projection.Reset();
	viewport.Reset();

	vertices.clear();
}