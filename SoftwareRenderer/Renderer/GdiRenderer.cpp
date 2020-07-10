#include "framework.h"
#include "GdiRenderer.h"
#include "FrameBuffer.h"
#include "Primitives/Point.h"

namespace Renderer
{
	GdiRenderer::GdiRenderer( const HWND hWnd, const int width, const int height )
		: hWnd( hWnd )
		, width( width )
		, height( height )
		, primitives()
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

	}

	void GdiRenderer::End()
	{

	}

	void GdiRenderer::Vertex( float x, float y, float z )
	{
		x = x * 100 + width * 0.5f;
		y = y * -100 + height * 0.5f;
		primitives.push_back( std::make_unique<Point>( x, y, z ) );
	}
}