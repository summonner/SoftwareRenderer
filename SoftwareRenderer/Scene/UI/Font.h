#pragma once
#include "Renderer/Mesh/Mesh.h"
#include "Renderer/Texturing/Texture2D.h"

class IRenderer;

class Font final
{
public:
	Font();
	~Font();
	static std::vector<Renderer::Vertex> BuildQuad( float x, float y, const Vector4& size );

	void Print( IRenderer& renderer, const char* message ) const;

private:
	std::vector<Renderer::Mesh> glyphs;
	std::shared_ptr<Renderer::Texture2D> texture;
};

