#include "framework.h"
#include "GdiRenderer.h"
#include "FrameBuffer.h"

GdiRenderer::GdiRenderer( const HWND& hWnd )
	: hWnd( hWnd )
{
}

GdiRenderer::~GdiRenderer()
{
}

void GdiRenderer::Clear()
{
	InvalidateRect( hWnd, nullptr, false );
}

void GdiRenderer::Present( const HDC& dc )
{
	FrameBuffer backBuffer( dc, 400, 300 );

	PatBlt( backBuffer.dc, 0, 0, backBuffer.width, backBuffer.height, BLACKNESS );
	for ( auto i = 0; i < 50; ++i )
	{
		SetPixel( backBuffer.dc, 50 + i, 50 + i, RGB( 0, 0, 255 ) );
		SetPixel( backBuffer.dc, 50 + i, 50, RGB( 0, 0, 255 ) );
		SetPixel( backBuffer.dc, 99, 50 + i, RGB( 0, 0, 255 ) );
	}

	Rectangle( backBuffer.dc, 100, 100, 200, 200 );
	BitBlt( dc, 0, 0, backBuffer.width, backBuffer.height, backBuffer.dc, 0, 0, SRCCOPY );
}
