#include "framework.h"
#include "NeHeSample.h"
#include "ILesson.h"
#include "../gl/glAdapter.h"
#include "Timer.h"
#include "Scene/UI/CommentUI.h"

NeHeSample::NeHeSample( std::unique_ptr<NeHe::ILesson> lesson )
	: lesson( std::move( lesson ) )
	, adapter( std::make_unique<glBridge>() )
	, keys{ 0, }
{
}

NeHeSample::~NeHeSample()
{
	adapter->Use( [this]() { 
		lesson->CleanGL();
		lesson.reset(); 
	} );
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

void NeHeSample::Update( const Timer& time )
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

	const auto description = lesson->GetDescription();
	if ( description != nullptr && description[0] != 0 )
	{
		CommentUI::Print( *renderer, description );
	}
}

void NeHeSample::OnMove( int x, int y )
{
	auto listener = dynamic_cast<IMouseInputListener*>(lesson.get());
	if ( listener == nullptr )
	{
		return;
	}

	listener->OnMove( x, y );
}

void NeHeSample::OnButton( UINT message )
{
	auto listener = dynamic_cast<IMouseInputListener*>(lesson.get());
	if ( listener == nullptr )
	{
		return;
	}

	adapter->Use( [listener, message]() { listener->OnButton( message ); } );
}