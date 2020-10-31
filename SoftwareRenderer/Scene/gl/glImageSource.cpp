#include "framework.h"
#include "glImageSource.h"


glImageSource::glImageSource( GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels, const Vector4& scale )
	: IImageSource( width, height )
	, pixels( pixels )
	, format( format )
	, convert( conversionTable[type] )
	, pixelSize( formatTable[format] )
	, scale( scale )
{
}

Color4 glImageSource::GetPixel( const Vector2Int& p ) const
{
	auto i = (p.y * width + p.x) * pixelSize;

	auto pixel = convert( pixels, format, i );
	pixel.x = std::clamp( (BYTE)(pixel.x * scale.x), (BYTE)0, (BYTE)255 );
	pixel.y = std::clamp( (BYTE)(pixel.y * scale.y), (BYTE)0, (BYTE)255 );
	pixel.z = std::clamp( (BYTE)(pixel.z * scale.z), (BYTE)0, (BYTE)255 );
	pixel.w = std::clamp( (BYTE)(pixel.w * scale.w), (BYTE)0, (BYTE)255 );
	return pixel;
}

template<typename T>
Color4 IntegerConverter( const GLvoid* buffer, GLenum format, int i )
{
	auto pixels = (T*)(buffer);
	switch ( format )
	{
	case GL_RGB:
		return Color4(	(BYTE)(pixels[i + 0]),
						(BYTE)(pixels[i + 1]),
						(BYTE)(pixels[i + 2]),
						255 );
	case GL_RGBA:
		return Color4(	(BYTE)(pixels[i + 0]),
						(BYTE)(pixels[i + 1]),
						(BYTE)(pixels[i + 2]),
						(BYTE)(pixels[i + 3]) );
	case GL_BGR_EXT:
		return Color4(	(BYTE)(pixels[i + 2]),
						(BYTE)(pixels[i + 1]),
						(BYTE)(pixels[i + 0]),
						255 );
	case GL_BGRA_EXT:
		return Color4(	(BYTE)(pixels[i + 2]),
						(BYTE)(pixels[i + 1]),
						(BYTE)(pixels[i + 0]),
						(BYTE)(pixels[i + 3]) );

	default:
		assert( "Not implemented yet" && false );
		return Color4::zero;
	}
}

template<typename T>
Color4 FloatConverter( const GLvoid* buffer, GLenum format, int i )
{
	auto pixels = (T*)(buffer);
	switch ( format )
	{
	case GL_RGB:
		return Color4(	(BYTE)(pixels[i + 0] * 255),
						(BYTE)(pixels[i + 1] * 255),
						(BYTE)(pixels[i + 2] * 255),
						255 );
	case GL_RGBA:
		return Color4(	(BYTE)(pixels[i + 0] * 255),
						(BYTE)(pixels[i + 1] * 255),
						(BYTE)(pixels[i + 2] * 255),
						(BYTE)(pixels[i + 3] * 255) );
	case GL_BGR_EXT:
		return Color4(	(BYTE)(pixels[i + 2] * 255),
						(BYTE)(pixels[i + 1] * 255),
						(BYTE)(pixels[i + 0] * 255),
						255 );
	case GL_BGRA_EXT:
		return Color4(	(BYTE)(pixels[i + 2] * 255),
						(BYTE)(pixels[i + 1] * 255),
						(BYTE)(pixels[i + 0] * 255),
						(BYTE)(pixels[i + 3] * 255) );
	default:
		assert( "Not implemented yet" && false );
		return Color4::zero;
	}
}

const Dictionary<GLenum, int> glImageSource::formatTable
{
	{ GL_RGB, 3 },
	{ GL_RGBA, 4 },
	{ GL_BGR_EXT, 3 },
	{ GL_BGRA_EXT, 4 },
};

const Dictionary<GLenum, glImageSource::ConvertFunc> glImageSource::conversionTable
{
	{ GL_UNSIGNED_BYTE, &IntegerConverter<BYTE> },
	{ GL_FLOAT, &FloatConverter<float> },
};