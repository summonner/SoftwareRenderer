#include "framework.h"
#include "glClipPlaneManager.h"

glClipPlaneManager::glClipPlaneManager()
	: planes( maxPlanes )
{
}

glClipPlaneManager::~glClipPlaneManager()
{
}

void glClipPlaneManager::Set( GLenum plane, const GLdouble* equation, const Renderer::Matrix& modelView )
{
	const auto i = ToIndex( plane );
	const Vector4 eq( (float)equation[0], (float)equation[1], (float)equation[2], (float)equation[3] );
	planes[i] = eq * modelView.Inverse();
}

const Vector4* glClipPlaneManager::Get( GLenum plane ) const
{
	const auto i = ToIndex( plane );
	return &planes[i];
}

int glClipPlaneManager::ToIndex( GLenum plane )
{
	return plane - GL_CLIP_PLANE0;
}