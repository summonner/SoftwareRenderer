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

WINGDIAPI void APIENTRY glRotatef( GLfloat angle, GLfloat x, GLfloat y, GLfloat z )
{
	renderer->Rotate( angle, x, y, z );
}

IRenderer::DrawMode Convert( GLenum mode )
{
	switch ( mode )
	{
	case GL_LINES:
		return IRenderer::DrawMode::Lines;
	case GL_LINE_STRIP:
		return IRenderer::DrawMode::LineStrip;
	case GL_LINE_LOOP:
		return IRenderer::DrawMode::LineLoop;
	case GL_TRIANGLES:
		return IRenderer::DrawMode::Triangles;
	case GL_QUADS:
		return IRenderer::DrawMode::Quads;
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
	renderer->SetColor( red, green, blue );
}

WINGDIAPI void APIENTRY glVertex3f( GLfloat x, GLfloat y, GLfloat z )
{
	renderer->AddVertex( x, y, z );
}


WINGDIAPI void APIENTRY glEnd( void )
{
	renderer->End();
}