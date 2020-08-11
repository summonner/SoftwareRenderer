#include "framework.h"
#include "GdiRenderer.h"
#include "FrameBuffer.h"
#include "Geometry/IGeometry.h"
#include "Rasterizer/IRasterizer.h"
#include "Rasterizer/RasterizedPixel.h"
#include "Rasterizer/DerivativeTexcoord.h"
#include "Math/Vector3.hpp"

namespace Renderer
{
	std::unique_ptr<GdiRenderer> GdiRenderer::Create( const HWND hWnd )
	{
		RECT rect;
		GetClientRect( hWnd, &rect );
		return std::make_unique<GdiRenderer>( hWnd, rect.right, rect.bottom );
	}

	GdiRenderer::GdiRenderer( const HWND hWnd, const int width, const int height )
		: IRenderer( width, height )
		, hWnd( hWnd )
		, bounds( width, height )
	{
		auto dc = GetDC( hWnd );
		backBuffer = std::make_unique<FrameBuffer>( dc, width, height );
		ReleaseDC( hWnd, dc );
	}
	
	GdiRenderer::~GdiRenderer()
	{
	}

	void GdiRenderer::Clear()
	{
		backBuffer->Clear();
	}

	void GdiRenderer::SetClearColor( float r, float g, float b, float a )
	{
		backBuffer->SetClearValue( Vector4( r, g, b, a ) );
	}

	void GdiRenderer::Present()
	{
		InvalidateRect( hWnd, nullptr, false );
	}

	void GdiRenderer::Present( const HDC dc )
	{
		backBuffer->BitBlt( dc );
	}

	void GdiRenderer::Render()
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
			rasterizer->Rasterize( bounds, [&]( const RasterizedPixel& p )
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

	void GdiRenderer::Draw( const Mesh& mesh )
	{
		generator.Begin( mesh.drawMode );
		vertices.reserve( mesh.size() );
		std::transform( mesh.begin(), mesh.end(), std::back_inserter( vertices ),
			[this]( const Vertex& v ) { return TransformVertex( v ); } );
//			std::bind( &GdiRenderer::TransformVertex, *this, std::placeholders::_1 ) );
		Render();
	}

	Vertex GdiRenderer::TransformVertex( Vertex v ) const
	{
		v.position = modelView * v.position;
		v.normal = Vector4( v.normal, 0 ) * modelView.Inverse();
		return v;
	}


	void GdiRenderer::Reset()
	{
		IRenderer::Reset();

		modelView.Reset();
		projection.Reset();
		viewport.Reset();

		vertices.clear();
		backBuffer->Reset();
	}
}