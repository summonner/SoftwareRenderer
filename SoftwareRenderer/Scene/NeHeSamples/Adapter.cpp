#include "framework.h"
#include "Adapter.h"
#include "Renderer/IRenderer.h"

std::shared_ptr<IRenderer> _renderer;
#define renderer _renderer

WINGDIAPI void APIENTRY glClear( GLbitfield mask )
{
	renderer->Clear();
}

WINGDIAPI void APIENTRY glLoadIdentity( void )
{
	renderer->LoadIdentity();
}

WINGDIAPI void APIENTRY glTranslatef( GLfloat x, GLfloat y, GLfloat z )
{
	renderer->Translate( x, y, z );
}

IRenderer::DrawMode Convert( GLenum mode )
{
	switch ( mode )
	{
	case GL_TRIANGLES:
		return IRenderer::DrawMode::Triangles;
	case GL_QUADS:
		return IRenderer::DrawMode::TriangleFan;
	case GL_POINTS:
	default:
		return IRenderer::DrawMode::Points;
	}
}

WINGDIAPI void APIENTRY glBegin( GLenum mode )
{
	auto drawMode = Convert( mode );
	renderer->Begin( drawMode );
}

WINGDIAPI void APIENTRY glColor3f( GLfloat red, GLfloat green, GLfloat blue )
{

}

WINGDIAPI void APIENTRY glVertex3f( GLfloat x, GLfloat y, GLfloat z )
{
	renderer->AddVertex( x, y, z );
}


WINGDIAPI void APIENTRY glEnd( void )
{
	renderer->End();
}