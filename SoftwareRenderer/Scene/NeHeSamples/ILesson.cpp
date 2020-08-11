#include "framework.h"
#include "ILesson.h"

namespace NeHe
{
	AUX_RGBImageRec* LoadBMP( LPCSTR filePath )
	{
		return auxDIBImageLoad( CA2CT( filePath ) );
	}

	GLvoid ILesson::ReSizeGLScene( GLsizei width, GLsizei height )			// Reshape The Window When It's Moved Or Resized
	{
		glViewport( 0, 0, width, height );									// Reset The Current Viewport
		glMatrixMode( GL_PROJECTION );										// Select The Projection Matrix
		glLoadIdentity();													// Reset The Projection Matrix
		gluPerspective( 45.0f, (GLfloat)(width) / (GLfloat)(height),			// Calculate The Aspect Ratio Of The Window
			1.0f, 1000.0f );
		glMatrixMode( GL_MODELVIEW );										// Select The Modelview Matrix
		glLoadIdentity();													// Reset The Modelview Matrix
	}
}