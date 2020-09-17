#pragma once
#include "Font.h"
#include "Renderer/Blending/BlendComponent.h"

class UI final
{
public:
	UI( int width, int height );
	~UI();

	void Begin( IRenderer& renderer );
	void End( IRenderer& renderer ) const;
	void Text( IRenderer& renderer, const Vector2& position, const char* message ) const;

private:
	Font font;
	const Vector2 size;

	class RenderState
	{
	public:
		RenderState();
		~RenderState();

		void Backup( const IRenderer& renderer );
		void Restore( IRenderer& renderer ) const;

	private:
		bool texture;
		Renderer::BlendComponent blend;
		bool depthTest;
		bool lighting;
		bool cullFace;
		bool stencil;
	} backup;
};