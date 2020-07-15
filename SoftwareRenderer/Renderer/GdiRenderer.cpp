#include "framework.h"
#include "GdiRenderer.h"
#include "FrameBuffer.h"
#include "Primitives/Point.h"
#include "PrimitiveGenerators/PrimitiveGenerator.h"
#include "Math/Vector3.hpp"
#include "Math/Matrix4x4.h"
#include "Renderer/RasterizedPixel.h"

namespace Renderer
{
	GdiRenderer::GdiRenderer( const HWND hWnd, const int width, const int height )
		: hWnd( hWnd )
		, width( width )
		, height( height )
		, primitives()
		, generator( std::make_unique<PrimitiveGenerator>() )
		, transform()
	{
		auto dc = GetDC( hWnd );
		backBuffer = std::make_unique<FrameBuffer>( dc, width, height );
		ReleaseDC( hWnd, dc );

		auto scale = Matrix4x4::Scale( Vector3( 100, 100, 1 ) );
		auto translate = Matrix4x4::Translate( Vector3( (float)width, (float)height, 0.f ) * 0.5f );
		view = translate * scale;
	}

	GdiRenderer* GdiRenderer::Create( const HWND hWnd )
	{
		RECT rect;
		GetClientRect( hWnd, &rect );
		return new GdiRenderer( hWnd, rect.right, rect.bottom );
	}

	GdiRenderer::~GdiRenderer()
	{
	}

	void GdiRenderer::Clear()
	{
		backBuffer->Clear();
		primitives.clear();
		vertices.clear();
	}

	void GdiRenderer::Present()
	{
		InvalidateRect( hWnd, nullptr, false );
	}

	void GdiRenderer::Present( const HDC dc )
	{
		for ( auto& vertex : vertices )
		{
			vertex.Rasterize( view );
		}

		generator->Generate( vertices, primitives );

		for ( const auto& pixel : *backBuffer )
		{
			const Vector2 pixelf( (float)pixel.x, (float)pixel.y );
			for ( const auto& primitive : primitives )
			{
				auto rasterized = primitive->Rasterize( pixelf );
				if ( rasterized.isValid == false )
				{
					continue;
				}

				backBuffer->SetPixel( pixel, (Vector3)rasterized.color );
			}
		}

		backBuffer->BitBlt( dc );
	}

	void GdiRenderer::Begin( DrawMode mode )
	{
		generator->Begin( mode, (int)vertices.size() );
	}

	void GdiRenderer::End()
	{
		generator->End( (int)vertices.size() );
	}

	void GdiRenderer::SetColor( float r, float g, float b )
	{
		temp.color = Vector4( r, g, b, 1 );
	}

	void GdiRenderer::AddVertex( float x, float y, float z )
	{
		Vector4 v( x, y, z, 1.f );
		auto t = transform * v;

		temp.position = t;
		vertices.push_back( temp );
	}

	void GdiRenderer::LoadIdentity()
	{
		transform = Matrix4x4::identity;
	}

	void GdiRenderer::Translate( float x, float y, float z )
	{
		transform = Matrix4x4::Translate( Vector3( x, y, z ) ) * transform;
	}

	void GdiRenderer::Rotate( Degree angle, float x, float y, float z )
	{
		transform = Matrix4x4::Rotate( angle * PI / 180, Vector3( x, y, z ) ) * transform;
	}

	void GdiRenderer::Scale( float x, float y, float z )
	{
		transform = Matrix4x4::Scale( Vector3( x, y, z ) ) * transform;
	}
}