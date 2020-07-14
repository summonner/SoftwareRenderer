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
	x = sin( t );
}

void SampleScene::Render( std::shared_ptr<IRenderer> renderer ) const
{
	renderer->Clear();

	renderer->Begin( IRenderer::DrawMode::Triangles );
	renderer->AddVertex( x + 0.f, 1.f, 0.f );
	renderer->AddVertex( x + -1.f, -1.f, 0.f );
	renderer->AddVertex( x + 1.f, -1.f, 0.f );
	renderer->End();

	renderer->Present();
}