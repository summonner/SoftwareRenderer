#include "framework.h"
#include "Lesson33.h"
#include "texture.h"											// Header File Containing Our Texture Structure ( NEW )

namespace NeHe
{
	Lesson33::Lesson33()
	{
	}

	Lesson33::~Lesson33()
	{
	}

	int Lesson33::LoadGLTextures()											// Load Bitmaps And Convert To Textures
	{
		int Status = FALSE;											// Status Indicator

		// Load The Bitmap, Check For Errors.
		if ( LoadTGA( &texture[0], "Data/Uncompressed.tga" ) &&
			LoadTGA( &texture[1], "Data/Compressed.tga" ) )
		{
			Status = TRUE;											// Set The Status To TRUE

			for ( int loop = 0; loop < 2; loop++ )						// Loop Through Both Textures
			{
				// Typical Texture Generation Using Data From The TGA ( CHANGE )
				glGenTextures( 1, &texture[loop].texID );				// Create The Texture ( CHANGE )
				glBindTexture( GL_TEXTURE_2D, texture[loop].texID );
				glTexImage2D( GL_TEXTURE_2D, 0, texture[loop].bpp / 8, texture[loop].width, texture[loop].height, 0, texture[loop].type, GL_UNSIGNED_BYTE, texture[loop].imageData );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

				if ( texture[loop].imageData )						// If Texture Image Exists ( CHANGE )
				{
					free( texture[loop].imageData );					// Free The Texture Image Memory ( CHANGE )
				}
			}
		}
		return Status;												// Return The Status
	}

	GLvoid Lesson33::ReSizeGLScene( GLsizei width, GLsizei height )				// Resize And Initialize The GL Window
	{
		if ( height == 0 )												// Prevent A Divide By Zero By
		{
			height = 1;												// Making Height Equal One
		}

		glViewport( 0, 0, width, height );								// Reset The Current Viewport

		glMatrixMode( GL_PROJECTION );								// Select The Projection Matrix
		glLoadIdentity();											// Reset The Projection Matrix

		// Calculate The Aspect Ratio Of The Window
		gluPerspective( 45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f );

		glMatrixMode( GL_MODELVIEW );									// Select The Modelview Matrix
		glLoadIdentity();											// Reset The Modelview Matrix
	}

	int Lesson33::InitGL( GLvoid )												// All Setup For OpenGL Goes Here
	{
		if ( !LoadGLTextures() )										// Jump To Texture Loading Routine ( NEW )
		{
			return FALSE;											// If Texture Didn't Load Return FALSE
		}

		glEnable( GL_TEXTURE_2D );									// Enable Texture Mapping ( NEW )
		glShadeModel( GL_SMOOTH );									// Enable Smooth Shading
		glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );						// Black Background
		glClearDepth( 1.0f );											// Depth Buffer Setup
		glEnable( GL_DEPTH_TEST );									// Enables Depth Testing
		glDepthFunc( GL_LEQUAL );										// The Type Of Depth Testing To Do
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );			// Really Nice Perspective Calculations

		return TRUE;												// Initialization Went OK
	}

	int Lesson33::DrawGLScene( GLvoid )											// Here's Where We Do All The Drawing
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );			// Clear The Screen And The Depth Buffer
		glLoadIdentity();											// Reset The Modelview Matrix
		glTranslatef( 0.0f, 0.0f, -10.0f );								// Translate 20 Units Into The Screen

		spin += 0.05f;												// Increase Spin

		for ( int loop = 0; loop < 20; loop++ )							// Loop Of 20
		{
			glPushMatrix();											// Push The Matrix
			glRotatef( spin + loop * 18.0f, 1.0f, 0.0f, 0.0f );				// Rotate On The X-Axis (Up - Down)
			glTranslatef( -2.0f, 2.0f, 0.0f );							// Translate 2 Units Left And 2 Up

			glBindTexture( GL_TEXTURE_2D, texture[0].texID );			// ( CHANGE )
			glBegin( GL_QUADS );										// Draw Our Quad
			glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, 0.0f );
			glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, 0.0f );
			glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, 0.0f );
			glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 0.0f );
			glEnd();												// Done Drawing The Quad
			glPopMatrix();											// Pop The Matrix

			glPushMatrix();											// Push The Matrix
			glTranslatef( 2.0f, 0.0f, 0.0f );							// Translate 2 Units To The Right
			glRotatef( spin + loop * 36.0f, 0.0f, 1.0f, 0.0f );				// Rotate On The Y-Axis (Left - Right)
			glTranslatef( 1.0f, 0.0f, 0.0f );							// Move One Unit Right

			glBindTexture( GL_TEXTURE_2D, texture[1].texID );			// ( CHANGE )
			glBegin( GL_QUADS );										// Draw Our Quad
			glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, 1.0f, 0.0f );
			glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, 1.0f, 0.0f );
			glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, -1.0f, 0.0f );
			glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, -1.0f, 0.0f );
			glEnd();												// Done Drawing The Quad
			glPopMatrix();											// Pop The Matrix
		}
		return TRUE;												// Keep Going
	}
}