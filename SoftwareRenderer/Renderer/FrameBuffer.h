#pragma once
class FrameBuffer final
{
public:
	FrameBuffer( const HDC dc, const int width, const int height );
	~FrameBuffer();

public:
	const HDC dc;
	const HBITMAP buffer;
	const int width;
	const int height;
};