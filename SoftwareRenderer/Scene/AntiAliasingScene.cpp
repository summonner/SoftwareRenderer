#include "framework.h"
#include "AntiAliasingScene.h"
#include "Renderer/IRenderer.h"
#include "Time.h"
#include "Renderer/Generators/PointGenerator.h"
#include "Renderer/Generators/LineGenerator.h"
#include "Scene/UI/CommentUI.h"

using Vertex = Renderer::Vertex;

AntiAliasingScene::AntiAliasingScene()
	: enableAA( true )
	, shape( 1 )
	, line( BuildLine() )
	, t( 0 )
{
}

AntiAliasingScene::~AntiAliasingScene()
{
}

void AntiAliasingScene::Init( const std::shared_ptr<IRenderer> renderer )
{
	renderer->blender.SetEnable( true );
	renderer->blender.SetBlendFunc( BlendFunc::SrcAlpha, BlendFunc::OneMinusSrcAlpha );
}

void AntiAliasingScene::OnResize( const std::shared_ptr<IRenderer> renderer, const int width, const int height )
{
	renderer->viewport.Set( 0, 0, width, height );
	renderer->projection.Reset();
	renderer->projection.Perspective( 45.f, (float)width / (float)height, 0.1f, 100.f );
}

void AntiAliasingScene::Update( const Time& time )
{
	t = time.GetTimeFromStart() * 0.1f;
}

void AntiAliasingScene::OnKeyboardInput( BYTE keyCode, bool isPressed )
{
	if ( isPressed == false )
	{
		return;
	}

	switch ( keyCode )
	{
	case ' ':
		shape = (shape + 1) % 2;
		break;

	case 'A':
		enableAA = !enableAA;
		break;
	}
}

void AntiAliasingScene::Render( const std::shared_ptr<IRenderer> renderer ) const
{
	static const Dictionary<int, std::function<void(const AntiAliasingScene&, IRenderer&)>> table
	{
		{ 0, &AntiAliasingScene::Points },
		{ 1, &AntiAliasingScene::Lines },
	};

	renderer->GetFrameBuffer().Clear();
	table[shape]( *this, *renderer );

	CommentUI::Print( *renderer, "A - Toggle Anti-Aliasing\nSpace - Change Shape" );
}

void AntiAliasingScene::Points( IRenderer& renderer ) const
{
	renderer.modelView.Reset();
	renderer.modelView.Translate( -2.5f, 0, -6 );
	Renderer::PointGenerator::SetSmooth( enableAA );

	Vertex v;
	for ( auto i = 0; i < 10; ++i )
	{
		Renderer::PointGenerator::SetSize( 5.f * i + 1.f );
		v.position = Vector4( i * 0.5f, sin( t + i ), 0.f, 1.f );
		renderer.Draw( Renderer::Mesh( DrawMode::Points, { v } ) );
	}
}

void AntiAliasingScene::Lines( IRenderer& renderer ) const
{
	renderer.modelView.Reset();
	renderer.modelView.Translate( 0, 0, -6 );
	renderer.modelView.Rotate( sin( t ) * 90.f, 0, 0, 1 );
	renderer.modelView.Translate( 0, -2, 0 );
	Renderer::LineGenerator::SetSmooth( enableAA );

	for ( auto i = 0; i < 10; ++i )
	{
		Renderer::LineGenerator::SetWidth( i + 1.f );
		renderer.Draw( line );
		renderer.modelView.Translate( 0.f, 0.4f, 0.f );
	}
}

Renderer::Mesh AntiAliasingScene::BuildLine()
{
	std::vector<Vertex> vertices( 2 );
	vertices[0].position.x = -2.f;
	vertices[0].color = Vector4( 1, 0, 0, 1 );
	vertices[1].position.x = 2.f;
	vertices[1].color = Vector4( 0, 1, 1, 1 );
	return Renderer::Mesh( DrawMode::Lines, vertices );
}
