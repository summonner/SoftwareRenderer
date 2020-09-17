#include "framework.h"
#include "Font.h"
#include "Renderer/IRenderer.h"
#include "Util/Bitmap.h"

Font::Font()
	: glyphs()
	, texture( nullptr )
{
	const auto bitmap = Bitmap::Load( _T( "Data/Font.bmp" ) );
	texture = std::make_shared<Renderer::Texture2D>( *bitmap, false );

	auto textureSize = texture->GetSize();
	auto glyphSize = Vector4( 16.f, 16.f, 0.f, 0.f );
	glyphSize.z = glyphSize.x / textureSize.x;
	glyphSize.w = glyphSize.y / textureSize.y;

	const auto maxGlyphs = 128;
	glyphs.reserve( maxGlyphs );
	for ( auto i = 0; i < maxGlyphs; ++i )
	{
		auto x = (i % 16) / 16.f;
		auto y = (i / 16) / 16.f;
		glyphs.emplace_back( DrawMode::Quads, BuildQuad( x, y, glyphSize ) );
	}
}

Font::~Font()
{
	glyphs.clear();
}

std::vector<Renderer::Vertex> Font::BuildQuad( float x, float y, const Vector4& size )
{
	std::vector<Renderer::Vertex> vertices( 4 );
	vertices[0].position = Vector4( 0.f, 0.f, 0.f, 1.f );
	vertices[0].texcoord = Vector2( x, 1 - y );

	vertices[3].position = Vector4( 0.f, size.y, 0.f, 1.f );
	vertices[3].texcoord = Vector2( x, 1 - y - size.w );

	vertices[2].position = Vector4( size.x, size.y, 0.f, 1.f );
	vertices[2].texcoord = Vector2( x + size.z, 1 - y - size.w );

	vertices[1].position = Vector4( size.x, 0.f, 0.f, 1.f );
	vertices[1].texcoord = Vector2( x + size.z, 1 - y );

	return vertices;
}

void Font::Print( IRenderer& renderer, const char* message ) const
{
	const Vector2 space( 10.f, 16.f );
	renderer.texture.Bind( texture );
	const auto length = strlen( message );
	auto x = 0;
	for ( auto i = 0u; i < length; ++i )
	{
		const char glyph = message[i];
		if ( glyph == '\n' )
		{
			renderer.modelView.Translate( space.x * -x, space.y, 0.f );
			x = 0;
			continue;
		}

		const auto index = glyph - 32u;
		if ( index >= glyphs.size() )
		{
			continue;
		}

		renderer.Draw( glyphs[index] );
		renderer.modelView.Translate( space.x, 0.f, 0.f );
		++x;
	}
}