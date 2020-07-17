#include "framework.h"
#include "SampleScene.h"
#include "Time.h"
#include "Renderer/IRenderer.h"

SampleScene::SampleScene()
{
}


SampleScene::~SampleScene()
{
}

float x = 0;
void SampleScene::Update( const Time& time )
{
	auto t = time.GetTimeFromStart();
	x = (sin( t ) + 1.f) * 0.5f;
}

void SampleScene::Render( std::shared_ptr<IRenderer> renderer ) const
{
	renderer->Clear();
	renderer->LoadIdentity();

//	renderer->Scale( x, x, x );
//	renderer->Rotate( x * 180.f, 0.f, 0.f, 1.f );
	renderer->Translate( -1.5f, 0.0f, -6.0f + 3 * x );
	renderer->Begin( IRenderer::DrawMode::Triangles );
	renderer->SetColor( 1.f, 0.f, 0.f );
	renderer->AddVertex( 0.f, 1.f, 0.f );
	renderer->SetColor( 0.f, 1.f, 0.f );
	renderer->AddVertex( -1.f, -1.f, 0.f );
	renderer->SetColor( 0.f, 0.f, 1.f );
	renderer->AddVertex( 1.f, -1.f, 0.f );
	renderer->End();

	//renderer->Translate( 3.0f, 0.0f, 0.0f );
	//renderer->Begin( IRenderer::DrawMode::TriangleFan );
	//renderer->SetColor( 0.5f, 0.5f, 1.0f );
	//renderer->AddVertex( -1.0f, 1.0f, 0.0f );
	//renderer->AddVertex( 1.0f, 1.0f, 0.0f );
	//renderer->AddVertex( 1.0f, -1.0f, 0.0f );
	//renderer->AddVertex( -1.0f, -1.0f, 0.0f );
	//renderer->End();

	renderer->Present();
}