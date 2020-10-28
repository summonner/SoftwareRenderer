#include "framework.h"
#include "Lesson31.h"
#include "MilkshapeModel.h"											// Header File For Milkshape File

namespace NeHe
{
	Lesson31::Lesson31()
	{
	}

	Lesson31::~Lesson31()
	{
	}

	GLuint Lesson31::LoadGLTexture( const char* filename )						// Load Bitmaps And Convert To Textures
	{
		AUX_RGBImageRec* pImage;										// Create Storage Space For The Texture
		GLuint texture = 0;												// Texture ID

		pImage = LoadBMP( filename );									// Loads The Bitmap Specified By filename

		// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
		if ( pImage != NULL && pImage->data != NULL )					// If Texture Image Exists
		{
			glGenTextures( 1, &texture );									// Create The Texture

			// Typical Texture Generation Using Data From The Bitmap
			glBindTexture( GL_TEXTURE_2D, texture );
			glTexImage2D( GL_TEXTURE_2D, 0, 3, pImage->sizeX, pImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pImage->data );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

			free( pImage->data );											// Free The Texture Image Memory
			free( pImage );												// Free The Image Structure
		}

		return texture;													// Return The Status
	}

	GLvoid Lesson31::ReSizeGLScene( GLsizei width, GLsizei height )					// Resize And Initialize The GL Window
	{
		if ( height == 0 )													// Prevent A Divide By Zero By
		{
			height = 1;													// Making Height Equal One
		}

		glViewport( 0, 0, width, height );									// Reset The Current Viewport

		glMatrixMode( GL_PROJECTION );									// Select The Projection Matrix
		glLoadIdentity();												// Reset The Projection Matrix

		// Calculate The Aspect Ratio Of The Window
		gluPerspective( 45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f );	// View Depth of 1000

		glMatrixMode( GL_MODELVIEW );										// Select The Modelview Matrix
		glLoadIdentity();												// Reset The Modelview Matrix
	}

	int Lesson31::InitGL( GLvoid )													// All Setup For OpenGL Goes Here
	{
		pModel = new MilkshapeModel();									// Memory To Hold The Model
		if ( pModel->loadModelData( "data/model.ms3d" ) == false )		// Loads The Model And Checks For Errors
		{
			MessageBox( NULL, _T( "Couldn't load the model data\\model.ms3d" ), _T( "Error" ), MB_OK | MB_ICONERROR );
		}

		pModel->reloadTextures();										// Loads Model Textures

		glEnable( GL_TEXTURE_2D );										// Enable Texture Mapping ( NEW )
		glShadeModel( GL_SMOOTH );										// Enable Smooth Shading
		glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );							// Black Background
		glClearDepth( 1.0f );												// Depth Buffer Setup
		glEnable( GL_DEPTH_TEST );										// Enables Depth Testing
		glDepthFunc( GL_LEQUAL );											// The Type Of Depth Testing To Do
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );				// Really Nice Perspective Calculations
		return TRUE;													// Initialization Went OK
	}

	int Lesson31::DrawGLScene( GLvoid )												// Here's Where We Do All The Drawing
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );				// Clear The Screen And The Depth Buffer
		glLoadIdentity();												// Reset The Modelview Matrix
		gluLookAt( 75, 75, 75, 0, 0, 0, 0, 1, 0 );						// (3) Eye Postion (3) Center Point (3) Y-Axis Up Vector

		glRotatef( yrot, 0.0f, 1.0f, 0.0f );									// Rotate On The Y-Axis By yrot

		pModel->draw();													// Draw The Model

		yrot += 1.0f;														// Increase yrot By One
		return TRUE;													// Keep Going
	}
}