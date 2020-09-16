#include "framework.h"
#include "Lesson4.h"

namespace NeHe
{
	Lesson4::Lesson4()
		: rtri( 0 )
		, rquad( 0 )
	{
	}

	Lesson4::~Lesson4()
	{
	}

	GLvoid Lesson4::ReSizeGLScene( GLsizei width, GLsizei height )		// Resize And Initialize The GL Window
	{
		if ( height == 0 )										// Prevent A Divide By Zero By
		{
			height = 1;										// Making Height Equal One
		}

		glViewport( 0, 0, width, height );						// Reset The Current Viewport

		glMatrixMode( GL_PROJECTION );						// Select The Projection Matrix
		glLoadIdentity();									// Reset The Projection Matrix

		// Calculate The Aspect Ratio Of The Window
		gluPerspective( 45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f );

		glMatrixMode( GL_MODELVIEW );							// Select The Modelview Matrix
		glLoadIdentity();									// Reset The Modelview Matrix
	}

	int Lesson4::InitGL( GLvoid )										// All Setup For OpenGL Goes Here
	{
		glShadeModel( GL_SMOOTH );							// Enable Smooth Shading
		glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );				// Black Background
		glClearDepth( 1.0f );									// Depth Buffer Setup
		glEnable( GL_DEPTH_TEST );							// Enables Depth Testing
		glDepthFunc( GL_LEQUAL );								// The Type Of Depth Testing To Do
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );	// Really Nice Perspective Calculations
		return TRUE;										// Initialization Went OK
	}

	int Lesson4::DrawGLScene( GLvoid )									// Here's Where We Do All The Drawing
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// Clear Screen And Depth Buffer
		glLoadIdentity();									// Reset The Current Modelview Matrix
		glTranslatef( -1.5f, 0.0f, -6.0f );						// Move Left 1.5 Units And Into The Screen 6.0
		glRotatef( rtri, 0.0f, 1.0f, 0.0f );						// Rotate The Triangle On The Y axis ( NEW )
		glBegin( GL_TRIANGLES );								// Start Drawing A Triangle
		glColor3f( 1.0f, 0.0f, 0.0f );						// Set Top Point Of Triangle To Red
		glVertex3f( 0.0f, 1.0f, 0.0f );					// First Point Of The Triangle
		glColor3f( 0.0f, 1.0f, 0.0f );						// Set Left Point Of Triangle To Green
		glVertex3f( -1.0f, -1.0f, 0.0f );					// Second Point Of The Triangle
		glColor3f( 0.0f, 0.0f, 1.0f );						// Set Right Point Of Triangle To Blue
		glVertex3f( 1.0f, -1.0f, 0.0f );					// Third Point Of The Triangle
		glEnd();											// Done Drawing The Triangle
		glLoadIdentity();									// Reset The Current Modelview Matrix
		glTranslatef( 1.5f, 0.0f, -6.0f );						// Move Right 1.5 Units And Into The Screen 6.0
		glRotatef( rquad, 1.0f, 0.0f, 0.0f );					// Rotate The Quad On The X axis ( NEW )
		glColor3f( 0.5f, 0.5f, 1.0f );							// Set The Color To Blue One Time Only
		glBegin( GL_QUADS );									// Draw A Quad
		glVertex3f( -1.0f, 1.0f, 0.0f );					// Top Left
		glVertex3f( 1.0f, 1.0f, 0.0f );					// Top Right
		glVertex3f( 1.0f, -1.0f, 0.0f );					// Bottom Right
		glVertex3f( -1.0f, -1.0f, 0.0f );					// Bottom Left
		glEnd();											// Done Drawing The Quad
		rtri += 0.2f;											// Increase The Rotation Variable For The Triangle ( NEW )
		rquad -= 0.15f;										// Decrease The Rotation Variable For The Quad ( NEW )
		return TRUE;										// Keep Going
	}
}