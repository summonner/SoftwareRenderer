#include "framework.h"
#include "GdiRenderer.h"
#include "FrameBuffer.h"
#include "Primitives/Point.h"
#include "PrimitiveGenerators/PrimitiveGeneratorFactory.h"
#include "PrimitiveGenerators/IPrimitiveGenerator.h"
#include "Math/Vector3.hpp"
#include "Math/Matrix4x4.h"

namespace Renderer
{
	std::function<IPrimitiveList( const std::vector<Vertex>& )> generator = nullptr;

	GdiRenderer::GdiRenderer( const HWND hWnd, const int width, const int height )
		: hWnd( hWnd )
		, width( width )
		, height( height )
		, primitives()
		, factory( std::make_unique<PrimitiveGeneratorFactory>() )
	{
		auto dc = GetDC( hWnd );
		backBuffer = std::make_unique<FrameBuffer>( dc, width, height );
		ReleaseDC( hWnd, dc );
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
		for ( const auto& pixel : *backBuffer )
		{
			for ( const auto& primitive : primitives )
			{
				if ( primitive->Contains( pixel ) == false )
				{
					continue;
				}

				SetPixel( backBuffer->dc, pixel.x, pixel.y, RGB( 255, 255, 255 ) );
			}
		}

		backBuffer->BitBlt( dc );
	}

	void GdiRenderer::Begin( DrawMode mode )
	{
		generator = factory->Create( mode );
	}

	void GdiRenderer::End()
	{
		if ( generator == nullptr )
		{
			return;
		}

		for ( auto& primitive : generator( vertices ) )
		{
			primitives.push_back( std::move( primitive ) );
		}

		generator = nullptr;
	}

	void GdiRenderer::AddVertex( float x, float y, float z )
	{
		if ( generator == nullptr )
		{
			return;
		}

		Vector4 v( x, y, z, 1.f );
		auto scale = Matrix4x4::Scale( Vector3( 100, -100, 1 ) );
		auto translate = Matrix4x4::Translate( Vector3( (float)width, (float)height, 0.f ) * 0.5f );
		auto rotate = Matrix4x4::Rotate( PI * 0.3f, Vector3( 0, 0, 1 ) );
		auto t = translate * scale * rotate * v;

		vertices.emplace_back<Vertex>( t );
	}
}