#include "framework.h"
#include "glFogManager.h"

glFogManager::glFogManager()
	: linear( std::make_shared<Renderer::FogFunc::Linear>() )
	, exp( std::make_shared<Renderer::FogFunc::Exp>( 1 ) )
	, exp2( std::make_shared<Renderer::FogFunc::Exp>( 2 ) )
	, current( exp )
{
}

glFogManager::~glFogManager()
{
}

void glFogManager::SetDensity( GLfloat param )
{
	exp->density = param;
	exp2->density = param;
}

void glFogManager::SetStart( GLfloat param )
{
	linear->start = param;
}

void glFogManager::SetEnd( GLfloat param )
{
	linear->end = param;
}

std::shared_ptr<const Renderer::IFogFunc> glFogManager::SetMode( GLint param )
{
	switch ( param )
	{
	case GL_LINEAR:
		current = linear;
		break;

	case GL_EXP:
		current = exp;
		break;

	case GL_EXP2:
		current = exp2;
		break;
	}

	return current;
}

std::shared_ptr<const Renderer::IFogFunc> glFogManager::GetMode() const
{
	return current;
}