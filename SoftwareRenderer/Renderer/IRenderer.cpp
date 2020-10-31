#include "framework.h"
#include "IRenderer.h"
#include "Geometry/IGeometry.h"
#include "Rasterizer/IRasterizer.h"
#include "Rasterizer/RasterizedPixel.h"
#include "Rasterizer/DerivativeTexcoord.h"
#include "Clipping/PlaneIterator.h"
#include "Math/Bounds.h"
using namespace Renderer;

IRenderer::IRenderer( std::unique_ptr<IFrameBuffer> frameBuffer )
	: backBuffer( std::move( frameBuffer ) )
	, depthBuffer( backBuffer->GetBounds() )
	, stencilBuffer( backBuffer->GetBounds() )
	, viewport( backBuffer->GetBounds() )
{
}
	
IRenderer::~IRenderer()
{
}

void IRenderer::Draw( const Mesh& mesh )
{
	RasterizeFunc f = [this]( Renderer::IRasterizer& rasterizer, const Bounds& bounds )
	{
		Rasterize( rasterizer, bounds );
	};
	Draw( mesh, f );
}

void IRenderer::Draw( const Mesh& mesh, RasterizeFunc rasterize )
{
	vertices.reserve( mesh.size() );
	std::transform( mesh.begin(), mesh.end(), std::back_inserter( vertices ),
		[this]( const Vertex& v ) 
		{ 
			return ProcessVertex( v ); 
		} );

	auto bounds = viewport.scissor.Get();
	backBuffer->Clear( bounds );
	depthBuffer.Clear( bounds );
	stencilBuffer.Clear( bounds );

	bounds = viewport.GetBounds();
	generator.Begin( mesh.drawMode );
	auto geometries = generator.Generate( vertices );
	for ( const auto& geometry : geometries )
	{
		auto rasterizer = geometry->Clip( viewport, planes );
		if ( rasterizer == nullptr )
		{
			continue;
		}

		rasterize( *rasterizer, bounds );
	}

	vertices.clear();
}

void IRenderer::Rasterize( Renderer::IRasterizer& rasterizer, const Bounds& bounds )
{
	const auto facet = cullFace.Apply( rasterizer.CheckFacet() );
	if ( facet == CullFaceComponent::Result::Cull )
	{
		return;
	}

	const auto mode = polygonMode.Get( facet == CullFaceComponent::Result::Front );
	const auto derivatives = rasterizer.Derivative( texture.IsEnable() );
	rasterizer.Rasterize( bounds, mode, [&]( const RasterizedPixel& p )
		{
			auto depthTest = [this, p]() { return depthBuffer.Test( p ); };
			if ( stencilBuffer.Test( p, depthTest ) == false )
			{
				return;
			}

			Vector4 color = p.GetColor();
			color *= texture.GetColor( p, derivatives );
			color = fog.Apply( p.GetEyeDepth(), color );

			backBuffer->SetPixel( p.coordinate, color, blender.AsFunc() );
		} );
}

Vertex IRenderer::ProcessVertex( Vertex v ) const
{
	assert( v.position.w == 1.f );

	v.position = modelView * v.position;
	v.normal = Vector4( v.normal, 0 ) * modelView.Inverse();
	v.normal = v.normal.Normalize();

	if ( texture.IsEnable() == true )
	{
		for ( auto i = 0; i < 2; ++i )
		{
			if ( texture.texGen[i].IsEnable() == false )
			{
				continue;
			}

			v.texcoord[i] = texture.texGen[i]( v, modelView );
		}
	}

	v.color = lighting.GetColor( v );

	v.view = v.position;
	v.position = projection * v.position;
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
	polygonMode.Reset();

	modelView.Reset();
	projection.Reset();
	viewport.Reset();

	vertices.clear();

	generator.Reset();
}

IDepthBufferController& IRenderer::GetDepthBuffer()
{
	return depthBuffer;
}

const IDepthBufferController& IRenderer::GetDepthBuffer() const
{
	return depthBuffer;
}

IFrameBufferController& IRenderer::GetFrameBuffer()
{
	return *backBuffer;
}

IStencilBufferController& IRenderer::GetStencilBuffer()
{
	return stencilBuffer;
}

const IStencilBufferController& IRenderer::GetStencilBuffer() const
{
	return stencilBuffer;
}