#include "framework.h"
#include "NeHeSample.h"
#include "ILesson.h"
#include "../gl/glAdapter.h"
#include "Time.h"

NeHeSample::NeHeSample( std::unique_ptr<NeHe::ILesson> lesson )
	: lesson( std::move( lesson ) )
	, adapter( std::make_unique<glBridge>() )
{
}

NeHeSample::~NeHeSample()
{
	adapter->Use( nullptr, [this]() { lesson->CleanGL(); } );
}

void NeHeSample::Init( const std::shared_ptr<IRenderer> renderer )
{
	adapter->Use( renderer.get(), [this]() { this->lesson->InitGL(); } );
}

void NeHeSample::OnResize( const std::shared_ptr<IRenderer> renderer, const int width, const int height )
{
	adapter->Use( renderer.get(), [&]() { lesson->ReSizeGLScene( width, height ); } );
}

void NeHeSample::Update( const Time& time )
{
	lesson->Update( (DWORD)(time.GetDeltaTime() * 1000) );
}

void NeHeSample::Render( const std::shared_ptr<IRenderer> renderer ) const
{
	adapter->Use( renderer.get(), [this]() { lesson->DrawGLScene(); } );
	renderer->Present();
}