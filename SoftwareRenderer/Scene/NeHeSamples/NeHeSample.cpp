#include "framework.h"
#include "NeHeSample.h"
#include "Renderer/IRenderer.h"

extern std::shared_ptr<IRenderer> _renderer;

int DrawGLScene();

NeHeSample::NeHeSample()
{
}

NeHeSample::~NeHeSample()
{
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