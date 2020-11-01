#include "framework.h"
#include "Lesson48.h"

namespace NeHe
{
	Lesson48::Lesson48()
	{
	}

	Lesson48::~Lesson48()
	{
	}

	int Lesson48::InitGL( GLvoid )						// Any GL Init Code & User Initialiazation Goes Here
	{
		// Start Of User Initialization
		isClicked = false;								            // NEW: Clicking The Mouse?
		isDragging = false;							                // NEW: Dragging The Mouse?

		glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );							// Black Background
		glClearDepth( 1.0f );											// Depth Buffer Setup
		glDepthFunc( GL_LEQUAL );										// The Type Of Depth Testing (Less Or Equal)
		glEnable( GL_DEPTH_TEST );										// Enable Depth Testing
		glShadeModel( GL_FLAT );											// Select Flat Shading (Nice Definition Of Objects)
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );				// Set Perspective Calculations To Most Accurate

		quadratic = gluNewQuadric();										// Create A Pointer To The Quadric Object
		gluQuadricNormals( quadratic, GLU_SMOOTH );						// Create Smooth Normals
		gluQuadricTexture( quadratic, GL_TRUE );							// Create Texture Coords

		glEnable( GL_LIGHT0 );											// Enable Default Light
		glEnable( GL_LIGHTING );											// Enable Lighting

		glEnable( GL_COLOR_MATERIAL );									// Enable Color Material

		return TRUE;													// Return TRUE (Initialization Successful)
	}

	int Lesson48::CleanGL( GLvoid )											// Any User DeInitialization Goes Here
	{
		gluDeleteQuadric( quadratic );
		return TRUE;
	}

	void Lesson48::Update( DWORD milliseconds, bool keys[] )									// Perform Motion Updates Here
	{
		if ( isRClicked )													// If Right Mouse Clicked, Reset All Rotations
		{
			Matrix3fSetIdentity( &LastRot );								// Reset Rotation
			Matrix3fSetIdentity( &ThisRot );								// Reset Rotation
			Matrix4fSetRotationFromMatrix3f( &Transform, &ThisRot );		// Reset Rotation
		}

		if ( !isDragging )												// Not Dragging
		{
			if ( isClicked )												// First Click
			{
				isDragging = true;										// Prepare For Dragging
				LastRot = ThisRot;										// Set Last Static Rotation To Last Dynamic One
				ArcBall.click( &MousePt );								// Update Start Vector And Prepare For Dragging
			}
		}
		else
		{
			if ( isClicked )												// Still Clicked, So Still Dragging
			{
				Quat4fT     ThisQuat;

				ArcBall.drag( &MousePt, &ThisQuat );						// Update End Vector And Get Rotation As Quaternion
				Matrix3fSetRotationFromQuat4f( &ThisRot, &ThisQuat );		// Convert Quaternion Into Matrix3fT
				Matrix3fMulMatrix3f( &ThisRot, &LastRot );				// Accumulate Last Rotation Into This One
				Matrix4fSetRotationFromMatrix3f( &Transform, &ThisRot );	// Set Our Final Transform's Rotation From This One
			}
			else														// No Longer Dragging
				isDragging = false;
		}
	}

	void Lesson48::Torus( float MinorRadius, float MajorRadius )					// Draw A Torus With Normals
	{
		int i, j;
		glBegin( GL_TRIANGLE_STRIP );									// Start A Triangle Strip
		for ( i = 0; i < 20; i++ )										// Stacks
		{
			for ( j = -1; j < 20; j++ )									// Slices
			{
				float wrapFrac = (j % 20) / (float)20;
				float phi = PI2 * wrapFrac;
				float sinphi = float( sin( phi ) );
				float cosphi = float( cos( phi ) );

				float r = MajorRadius + MinorRadius * cosphi;

				glNormal3f( float( sin( PI2 * (i % 20 + wrapFrac) / (float)20 ) ) * cosphi, sinphi, float( cos( PI2 * (i % 20 + wrapFrac) / (float)20 ) ) * cosphi );
				glVertex3f( float( sin( PI2 * (i % 20 + wrapFrac) / (float)20 ) ) * r, MinorRadius * sinphi, float( cos( PI2 * (i % 20 + wrapFrac) / (float)20 ) ) * r );

				glNormal3f( float( sin( PI2 * (i + 1 % 20 + wrapFrac) / (float)20 ) ) * cosphi, sinphi, float( cos( PI2 * (i + 1 % 20 + wrapFrac) / (float)20 ) ) * cosphi );
				glVertex3f( float( sin( PI2 * (i + 1 % 20 + wrapFrac) / (float)20 ) ) * r, MinorRadius * sinphi, float( cos( PI2 * (i + 1 % 20 + wrapFrac) / (float)20 ) ) * r );
			}
		}
		glEnd();														// Done Torus
	}

	int Lesson48::DrawGLScene( GLvoid )
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );				// Clear Screen And Depth Buffer
		glLoadIdentity();												// Reset The Current Modelview Matrix
		glTranslatef( -1.5f, 0.0f, -6.0f );									// Move Left 1.5 Units And Into The Screen 6.0

		glPushMatrix();													// NEW: Prepare Dynamic Transform
		glMultMatrixf( Transform.M );										// NEW: Apply Dynamic Transform
		glColor3f( 0.75f, 0.75f, 1.0f );
		Torus( 0.30f, 1.00f );
		glPopMatrix();													// NEW: Unapply Dynamic Transform

		glLoadIdentity();												// Reset The Current Modelview Matrix
		glTranslatef( 1.5f, 0.0f, -6.0f );									// Move Right 1.5 Units And Into The Screen 7.0

		glPushMatrix();													// NEW: Prepare Dynamic Transform
		glMultMatrixf( Transform.M );										// NEW: Apply Dynamic Transform
		glColor3f( 1.0f, 0.75f, 0.75f );
		gluSphere( quadratic, 1.3f, 20, 20 );
		glPopMatrix();													// NEW: Unapply Dynamic Transform

		glFlush();														// Flush The GL Rendering Pipeline
		return TRUE;
	}

	const char* Lesson48::GetDescription() const
	{
		return "Drag - Rotate\n\
				RButton - Reset";
	}

	void Lesson48::OnMove( int x, int y )
	{
		MousePt.s.X = (GLfloat)x;
		MousePt.s.Y = (GLfloat)y;
	}

	void Lesson48::OnButton( UINT message )
	{
		switch ( message )
		{
		case WM_LBUTTONDOWN:
			isClicked = true;
			break;
		case WM_LBUTTONUP:
			isClicked = false;
			break;
		case WM_RBUTTONDOWN:
			isRClicked = true;
			break;
		case WM_RBUTTONUP:
			isRClicked = false;
			break;
		}
	}
}