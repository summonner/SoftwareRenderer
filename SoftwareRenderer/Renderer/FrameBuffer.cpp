#include "framework.h"
#include "FrameBuffer.h"


FrameBuffer::FrameBuffer( const HDC& dc, const int width, const int height )
	: dc( CreateCompatibleDC( dc ) )
	, buffer( CreateCompatibleBitmap( dc, width, height ) )
	, width( width )
	, height( height )
{
	SelectObject( this->dc, buffer );
}


FrameBuffer::~FrameBuffer()
{
	DeleteObject( buffer );
	DeleteDC( dc );
}
