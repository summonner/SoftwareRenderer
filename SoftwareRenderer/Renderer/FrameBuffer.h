#pragma once
class FrameBuffer final
{
public:
	FrameBuffer( const HDC dc, const int width, const int height );
	~FrameBuffer();

	void Clear();
	void BitBlt( const HDC dc );

public:
	const HDC dc;
	const HBITMAP buffer;
	const int width;
	const int height;
};