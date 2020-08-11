#include "framework.h"
#include "NeHeSample.h"
#include "ILesson.h"
#include "../gl/glAdapter.h"
#include "Time.h"

NeHeSample::NeHeSample( std::unique_ptr<NeHe::ILesson> lesson )
	: lesson( std::move( lesson ) )
	, adapter( std::make_unique<glBridge>() )
	, keys{ 0, }
{
}

NeHeSample::~NeHeSample()
{
	adapter->Use( [this]() { lesson->CleanGL(); } );
	adapter->renderer = nullptr;
}

void NeHeSample::Init( const std::shared_ptr<IRenderer> renderer )
{
	adapter->Init( renderer );
	adapter->Use( [this]() { lesson->InitGL(); } );
}

void NeHeSample::OnResize( const std::shared_ptr<IRenderer> renderer, const int width, const int height )
{
	adapter->Use( [&]() { lesson->ReSizeGLScene( width, height ); } );
}

void NeHeSample::Update( const Time& time )
{
	adapter->Use( [&]() { lesson->Update( (DWORD)(time.GetDeltaTime() * 1000), keys ); } );
}

void NeHeSample::OnKeyboardInput( BYTE keycode, bool isPressed )
{
	keys[keycode] = isPressed;
}

void NeHeSample::Render( const std::shared_ptr<IRenderer> renderer ) const
{
	adapter->Use( [this]() { lesson->DrawGLScene(); } );
}