#pragma once
#include "glAdapter.h"
#include "Util/IImageSource.h"

class glImageSource final : public IImageSource
{
public:
	glImageSource( GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels, const Vector4& scale );

	Color4 GetPixel( const Vector2Int& p ) const override;

private:
	using ConvertFunc = std::function<Color4( const GLvoid* pixels, GLenum format, int i )>;
	static const Dictionary<GLenum, ConvertFunc> conversionTable;
	static const Dictionary<GLenum, int> formatTable;

	const GLvoid* pixels;
	const GLenum format;
	const ConvertFunc convert;
	const int pixelSize;
	const Vector4& scale;
};