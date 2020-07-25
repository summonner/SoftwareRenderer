#pragma once
#include "glAdapter.h"
#include "Util/IImageSource.h"
#include "Util/Dictionary.hpp"

namespace Renderer
{
	class ITexture;
}
using ITexture = Renderer::ITexture;
class IRenderer;

class glTextureManager final
{
public:
	glTextureManager();
	~glTextureManager();

	void Generate( int num, GLuint* outHandles );
	void Delete( GLuint handle );
	std::shared_ptr<ITexture> Bind( GLuint handle );
	void SetImage( GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels );

private:
	Dictionary<GLuint, std::shared_ptr<ITexture>> textures;
	GLuint current;


	class glImageSource final : public IImageSource
	{
	public:
		glImageSource( GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels );

		Color4 GetPixel( const Vector2Int& p ) const override;

	private:
		const BYTE* pixels;
		const GLenum format;
		const int pixelSize;
	};
};