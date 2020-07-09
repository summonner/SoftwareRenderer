#include "framework.h"
#include "FrameBuffer.h"


FrameBuffer::FrameBuffer( const HDC source, const int width, const int height )
	: dc( CreateCompatibleDC( source ) )
	, buffer( CreateCompatibleBitmap( source, width, height ) )
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

void FrameBuffer::Clear()
{
	PatBlt( dc, 0, 0, width, height, BLACKNESS );
}

void FrameBuffer::BitBlt( const HDC source )
{
	::BitBlt( source, 0, 0, width, height, dc, 0, 0, SRCCOPY );
}