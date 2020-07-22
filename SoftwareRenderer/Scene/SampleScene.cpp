#include "framework.h"
#include "SampleScene.h"
#include "Time.h"
#include "Renderer/IRenderer.h"

SampleScene::SampleScene()
	: checker( Bitmap::Load( _T( "Data/Checker.bmp" ) ) )
{
	
}


SampleScene::~SampleScene()
{
}

float x = 0;
void SampleScene::Update( const Time& time )
{
	auto t = time.GetTimeFromStart();
	x = (sin( t ));// +1.f) * 0.5f;
}

void SampleScene::Render( std::shared_ptr<IRenderer> renderer ) const
{
	renderer->Clear();
	renderer->LoadIdentity();

//	renderer->Scale( x, x, x );
//	renderer->Scale( 1, -1, 1 );
	renderer->BindTexture( checker );
	renderer->Translate( -1.5f, 0.0f, -6.0f + 3 * 0 );
	renderer->Rotate( x * -90.f, 0.f, 1.f, 0.f );
	renderer->Begin( IRenderer::DrawMode::Triangles );
	renderer->SetColor( 1.f, 0.f, 0.f );
	renderer->TexCoord( 0.5f, 1.0f );
	renderer->AddVertex( 0.f, 1.f, 0.f );

	renderer->SetColor( 0.f, 1.f, 0.f );
	renderer->TexCoord( 0.0f, 0.0f );
	renderer->AddVertex( -1.f, -1.f, 0.f );

	renderer->SetColor( 0.f, 0.f, 1.f );
	renderer->TexCoord( 1.0f, 0.0f );
	renderer->AddVertex( 1.f, -1.f, 0.f );
	renderer->End();

	renderer->LoadIdentity();
	renderer->BindTexture( checker );
	renderer->Translate( 1.5f, 0.0f, -6.0f );
	renderer->Rotate( x * 90.f, 1.f, 0.f, 0.f );
	renderer->Begin( IRenderer::DrawMode::Quads );
	renderer->SetColor( 1.0f, 0.5f, 0.5f );
	renderer->TexCoord( 0.0f, 1.0f );
	renderer->AddVertex( -1.0f, 1.0f, 0.0f );

	renderer->SetColor( 0.5f, 0.5f, 0.5f );
	renderer->TexCoord( 0.0f, 0.0f );
	renderer->AddVertex( -1.0f, -1.0f, 0.0f );

	renderer->SetColor( 0.5f, 0.5f, 1.0f );
	renderer->TexCoord( 1.0f, 0.0f );
	renderer->AddVertex( 1.0f, -1.0f, 0.0f );

	renderer->SetColor( 0.5f, 1.0f, 0.5f );
	renderer->TexCoord( 1.0f, 1.0f );
	renderer->AddVertex( 1.0f, 1.0f, 0.0f );
	renderer->End();

	renderer->Present();
}