#include "framework.h"
#include "GdiRenderer.h"
#include "FrameBuffer.h"


GdiRenderer::GdiRenderer( const HWND hWnd, const int width, const int height )
	: hWnd( hWnd )
	, width( width )
	, height( height )
{
	auto dc = GetDC( hWnd );
	backBuffer = new FrameBuffer( dc, width, height );
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
	SAFE_DELETE( backBuffer );
}

void GdiRenderer::Clear()
{
	backBuffer->Clear();
}

void GdiRenderer::Present()
{
	InvalidateRect( hWnd, nullptr, false );
}

void GdiRenderer::Present( const HDC dc )
{
	for ( auto i = 0; i < 50; ++i )
	{
		SetPixel( backBuffer->dc, 50 + i, 50 + i, RGB( 0, 0, 255 ) );
		SetPixel( backBuffer->dc, 50 + i, 50, RGB( 0, 0, 255 ) );
		SetPixel( backBuffer->dc, 99, 50 + i, RGB( 0, 0, 255 ) );
	}
	Rectangle( backBuffer->dc, 100, 100, 200, 200 );

	backBuffer->BitBlt( dc );
}
