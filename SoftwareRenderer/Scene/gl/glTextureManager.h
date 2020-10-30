#pragma once
#include "glAdapter.h"
#include "Util/IImageSource.h"
#include "Util/Dictionary.hpp"
#include "Renderer/Texturing/WrapMode.h"

namespace Renderer
{
	class ITexture;
	class Texture2D;
}
using ITexture = Renderer::ITexture;
using Texture2D = Renderer::Texture2D;
class IRenderer;

class glTextureManager final
{
public:
	glTextureManager();
	~glTextureManager();

	void Generate( int num, GLuint* outHandles );
	void Delete( GLuint handle );
	std::shared_ptr<ITexture> Bind( GLuint handle );
	std::shared_ptr<ITexture> SetImage( GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels );
	std::shared_ptr<ITexture> SetSubImage( GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels );

	void SetWrapModeS( GLint param );
	void SetWrapModeT( GLint param );
	void SetMinFilter( GLint param );
	void SetMagFilter( GLint param );

	void SetPixel( const Vector2Int& p, int mipLevel, const Vector4& value );
	Vector4 scale = Vector4::one;

private:
	std::shared_ptr<Texture2D> Get2D() const;
	Dictionary<GLuint, std::shared_ptr<ITexture>> textures;
	GLuint current;

private:
	static const Dictionary<GLenum, int> formatTable;
	static const Dictionary<GLint, TextureWrapMode> wrapModeTable;

	class glImageSource final : public IImageSource
	{
	public:
		glImageSource( GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels, const Vector4& scale );

		Color4 GetPixel( const Vector2Int& p ) const override;

	private:
		const BYTE* const pixels;
		const GLenum format;
		const int pixelSize;
		const Vector4& scale;
	};
};