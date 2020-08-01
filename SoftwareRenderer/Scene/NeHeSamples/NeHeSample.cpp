#include "framework.h"
#include "NeHeSample.h"
#include "ILesson.h"
#include "../gl/glAdapter.h"

NeHeSample::NeHeSample( std::shared_ptr<IRenderer> renderer, std::unique_ptr<NeHe::ILesson> lesson )
	: lesson( std::move( lesson ) )
{
	_renderer = renderer;
	this->lesson->InitGL();
	_renderer = nullptr;
}

NeHeSample::~NeHeSample()
{
	lesson->CleanGL();
}

void NeHeSample::Update( const Time& time )
{
}

void NeHeSample::Render( std::shared_ptr<IRenderer> renderer ) const
{
	_renderer = renderer;
	lesson->DrawGLScene();
	_renderer = nullptr;

	renderer->Present();
}