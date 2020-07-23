#include "framework.h"
#include "NeHeSample.h"
#include "../gl/glAdapter.h"

int InitGL();
int DrawGLScene();
int CleanGL();

NeHeSample::NeHeSample( std::shared_ptr<IRenderer> renderer )
{
	_renderer = renderer;
	InitGL();
	_renderer = nullptr;
}

NeHeSample::~NeHeSample()
{
	CleanGL();
}

void NeHeSample::Update( const Time& time )
{
}

void NeHeSample::Render( std::shared_ptr<IRenderer> renderer ) const
{
	_renderer = renderer;
	DrawGLScene();
	_renderer = nullptr;

	renderer->Present();
}