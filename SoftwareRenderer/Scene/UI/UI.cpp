#include "framework.h"
#include "UI.h"
#include "Renderer/IRenderer.h"

UI::UI( int width, int height )
	: font()
	, size( (float)width, (float)height )
{
}

UI::~UI()
{
}

void UI::Begin( IRenderer& renderer )
{
	backup.Backup( renderer );

	renderer.texture.SetEnable( true );
	renderer.blender.SetEnable( true );
	renderer.blender.SetBlendFunc( BlendFunc::One, BlendFunc::One );
	renderer.GetDepthBuffer().SetEnable( false );
	renderer.lighting.SetEnable( false );
	renderer.cullFace.SetEnable( false );
	renderer.fog.SetEnable( false );

	renderer.projection.Push();
	renderer.projection.Reset();
	renderer.projection.Ortho( 0, size.x, size.y, 0, -1, 1 );

	renderer.modelView.Push();
}

void UI::End( IRenderer& renderer ) const
{
	renderer.projection.Pop();
	renderer.modelView.Pop();

	backup.Restore( renderer );
}

void UI::Text( IRenderer& renderer, const Vector2& position, const char* message ) const
{
	renderer.modelView.Reset();
	renderer.modelView.Translate( position.x, position.y, 0.f );

	font.Print( renderer, message );
}

UI::RenderState::RenderState()
	: texture()
	, blend()
	, depthTest( false )
	, lighting( false )
	, cullFace( false )
	, stencil( false )
	, fog( false )
{
}

UI::RenderState::~RenderState()
{
}

void UI::RenderState::Backup( const IRenderer& renderer )
{
	texture = renderer.texture;
	blend = renderer.blender;
	depthTest = renderer.GetDepthBuffer().IsEnable();
	lighting = renderer.lighting.IsEnable();
	cullFace = renderer.cullFace.IsEnable();
	stencil = renderer.GetStencilBuffer().IsEnable();
	fog = renderer.fog.IsEnable();
}

void UI::RenderState::Restore( IRenderer& renderer ) const
{
	renderer.texture = texture;
	renderer.blender = blend;
	renderer.GetDepthBuffer().SetEnable( depthTest );
	renderer.lighting.SetEnable( lighting );
	renderer.cullFace.SetEnable( cullFace );
	renderer.GetStencilBuffer().SetEnable( stencil );
	renderer.fog.SetEnable( fog );
}