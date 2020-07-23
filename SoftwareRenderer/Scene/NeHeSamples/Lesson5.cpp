#include "framework.h"
#include "../gl/glAdapter.h"

GLfloat	rtri;				// Angle For The Triangle ( NEW )
GLfloat	rquad;				// Angle For The Quad ( NEW )

int DrawGLScene( GLvoid )									// Here's Where We Do All The Drawing
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef( -1.5f, 0.0f, -6.0f );						// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef( rtri, 0.0f, 1.0f, 0.0f );						// Rotate The Triangle On The Y axis ( NEW )
	glBegin( GL_TRIANGLES );								// Start Drawing A Triangle
	glColor3f( 1.0f, 0.0f, 0.0f );						// Red
	glVertex3f( 0.0f, 1.0f, 0.0f );					// Top Of Triangle (Front)
	glColor3f( 0.0f, 1.0f, 0.0f );						// Green
	glVertex3f( -1.0f, -1.0f, 1.0f );					// Left Of Triangle (Front)
	glColor3f( 0.0f, 0.0f, 1.0f );						// Blue
	glVertex3f( 1.0f, -1.0f, 1.0f );					// Right Of Triangle (Front)
	glColor3f( 1.0f, 0.0f, 0.0f );						// Red
	glVertex3f( 0.0f, 1.0f, 0.0f );					// Top Of Triangle (Right)
	glColor3f( 0.0f, 0.0f, 1.0f );						// Blue
	glVertex3f( 1.0f, -1.0f, 1.0f );					// Left Of Triangle (Right)
	glColor3f( 0.0f, 1.0f, 0.0f );						// Green
	glVertex3f( 1.0f, -1.0f, -1.0f );					// Right Of Triangle (Right)
	glColor3f( 1.0f, 0.0f, 0.0f );						// Red
	glVertex3f( 0.0f, 1.0f, 0.0f );					// Top Of Triangle (Back)
	glColor3f( 0.0f, 1.0f, 0.0f );						// Green
	glVertex3f( 1.0f, -1.0f, -1.0f );					// Left Of Triangle (Back)
	glColor3f( 0.0f, 0.0f, 1.0f );						// Blue
	glVertex3f( -1.0f, -1.0f, -1.0f );					// Right Of Triangle (Back)
	glColor3f( 1.0f, 0.0f, 0.0f );						// Red
	glVertex3f( 0.0f, 1.0f, 0.0f );					// Top Of Triangle (Left)
	glColor3f( 0.0f, 0.0f, 1.0f );						// Blue
	glVertex3f( -1.0f, -1.0f, -1.0f );					// Left Of Triangle (Left)
	glColor3f( 0.0f, 1.0f, 0.0f );						// Green
	glVertex3f( -1.0f, -1.0f, 1.0f );					// Right Of Triangle (Left)
	glEnd();											// Done Drawing The Pyramid

	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef( 1.5f, 0.0f, -7.0f );						// Move Right 1.5 Units And Into The Screen 7.0
	glRotatef( rquad, 1.0f, 1.0f, 1.0f );					// Rotate The Quad On The X axis ( NEW )
	glBegin( GL_QUADS );									// Draw A Quad
	glColor3f( 0.0f, 1.0f, 0.0f );						// Set The Color To Green
	glVertex3f( 1.0f, 1.0f, -1.0f );					// Top Right Of The Quad (Top)
	glVertex3f( -1.0f, 1.0f, -1.0f );					// Top Left Of The Quad (Top)
	glVertex3f( -1.0f, 1.0f, 1.0f );					// Bottom Left Of The Quad (Top)
	glVertex3f( 1.0f, 1.0f, 1.0f );					// Bottom Right Of The Quad (Top)
	glColor3f( 1.0f, 0.5f, 0.0f );						// Set The Color To Orange
	glVertex3f( 1.0f, -1.0f, 1.0f );					// Top Right Of The Quad (Bottom)
	glVertex3f( -1.0f, -1.0f, 1.0f );					// Top Left Of The Quad (Bottom)
	glVertex3f( -1.0f, -1.0f, -1.0f );					// Bottom Left Of The Quad (Bottom)
	glVertex3f( 1.0f, -1.0f, -1.0f );					// Bottom Right Of The Quad (Bottom)
	glColor3f( 1.0f, 0.0f, 0.0f );						// Set The Color To Red
	glVertex3f( 1.0f, 1.0f, 1.0f );					// Top Right Of The Quad (Front)
	glVertex3f( -1.0f, 1.0f, 1.0f );					// Top Left Of The Quad (Front)
	glVertex3f( -1.0f, -1.0f, 1.0f );					// Bottom Left Of The Quad (Front)
	glVertex3f( 1.0f, -1.0f, 1.0f );					// Bottom Right Of The Quad (Front)
	glColor3f( 1.0f, 1.0f, 0.0f );						// Set The Color To Yellow
	glVertex3f( 1.0f, -1.0f, -1.0f );					// Top Right Of The Quad (Back)
	glVertex3f( -1.0f, -1.0f, -1.0f );					// Top Left Of The Quad (Back)
	glVertex3f( -1.0f, 1.0f, -1.0f );					// Bottom Left Of The Quad (Back)
	glVertex3f( 1.0f, 1.0f, -1.0f );					// Bottom Right Of The Quad (Back)
	glColor3f( 0.0f, 0.0f, 1.0f );						// Set The Color To Blue
	glVertex3f( -1.0f, 1.0f, 1.0f );					// Top Right Of The Quad (Left)
	glVertex3f( -1.0f, 1.0f, -1.0f );					// Top Left Of The Quad (Left)
	glVertex3f( -1.0f, -1.0f, -1.0f );					// Bottom Left Of The Quad (Left)
	glVertex3f( -1.0f, -1.0f, 1.0f );					// Bottom Right Of The Quad (Left)
	glColor3f( 1.0f, 0.0f, 1.0f );						// Set The Color To Violet
	glVertex3f( 1.0f, 1.0f, -1.0f );					// Top Right Of The Quad (Right)
	glVertex3f( 1.0f, 1.0f, 1.0f );					// Top Left Of The Quad (Right)
	glVertex3f( 1.0f, -1.0f, 1.0f );					// Bottom Left Of The Quad (Right)
	glVertex3f( 1.0f, -1.0f, -1.0f );					// Bottom Right Of The Quad (Right)
	glEnd();											// Done Drawing The Quad

	rtri += 0.2f;											// Increase The Rotation Variable For The Triangle ( NEW )
	rquad -= 0.15f;										// Decrease The Rotation Variable For The Quad ( NEW )
	return TRUE;										// Keep Going
}