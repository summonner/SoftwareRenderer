#include "framework.h"
#include "ILesson.h"
#include "../gl/AUX_RGBImageRec.h"

namespace NeHe
{
	AUX_RGBImageRec* LoadBMP( LPCSTR filePath )
	{
		return auxDIBImageLoad( CA2CT( filePath ) );
	}

	AUX_RGBImageRec* ILesson::auxDIBImageLoad( LPCSTR filePath )
	{
		return ::auxDIBImageLoad( CA2CT( filePath ) );
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

	FILE* ILesson::fopen( const char* filename, const char* mode )
	{
		FILE* file;
		auto err = fopen_s( &file, filename, mode );
		if ( err != 0 )
		{
			return nullptr;
		}

		return file;
	}
}