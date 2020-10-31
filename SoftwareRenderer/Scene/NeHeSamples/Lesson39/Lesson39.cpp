#include "framework.h"
#include "Lesson39.h"

namespace NeHe
{
	Lesson39::Lesson39()
	{
	}

	Lesson39::~Lesson39()
	{
	}

	int Lesson39::LoadGLTextures()                                    // Load Bitmaps And Convert To Textures
	{
		int Status = FALSE;                               // Status Indicator
		AUX_RGBImageRec* TextureImage[1];               // Create Storage Space For The Textures
		memset( TextureImage, 0, sizeof( void* ) * 1 );        // Set The Pointer To NULL

		int loop = 0;
		if ( (TextureImage[0] = LoadBMP( "Data/Font.bmp" )) )
		{
			Status = TRUE;                            // Set The Status To TRUE

			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[loop]->sizeX, TextureImage[loop]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[loop]->data );
		}

		for ( loop = 0; loop < 1; loop++ )
		{
			if ( TextureImage[loop] )							// If Texture Exists
			{
				if ( TextureImage[loop]->data )			// If Texture Image Exists
				{
					free( TextureImage[loop]->data );	// Free The Texture Image Memory
				}
				free( TextureImage[loop] );				// Free The Image Structure
			}
		}
		return Status;                                  // Return The Status
	}

#define GLYPH_WIDTH 10.0
	GLvoid Lesson39::BuildFont()								// Build Our Bitmap Font
	{
		LoadGLTextures();
		base = glGenLists( 256 );									// Creating 256 Display Lists

		for ( auto loop1 = 0; loop1 < 256; loop1++ )						// Loop Through All 256 Lists
		{
			float cx = float( loop1 % 16 ) / 16.0f;						// X Position Of Current Character
			float cy = float( loop1 / 16 ) / 16.0f;						// Y Position Of Current Character

			glNewList( base + loop1, GL_COMPILE );					// Start Building A List
			glBegin( GL_QUADS );								// Use A Quad For Each Character
			glTexCoord2f( cx, 1.0f - cy );			// Texture Coord (Bottom Left)
			glVertex2d( 0, 16 );							// Vertex Coord (Bottom Left)
			glTexCoord2f( cx + 0.0625f, 1.0f - cy );	// Texture Coord (Bottom Right)
			glVertex2i( 16, 16 );							// Vertex Coord (Bottom Right)
			glTexCoord2f( cx + 0.0625f, 1.0f - cy - 0.0625f );			// Texture Coord (Top Right)
			glVertex2i( 16, 0 );							// Vertex Coord (Top Right)
			glTexCoord2f( cx, 1.0f - cy - 0.0625f );					// Texture Coord (Top Left)
			glVertex2i( 0, 0 );							// Vertex Coord (Top Left)
			glEnd();										// Done Building Our Quad (Character)
			glTranslated( GLYPH_WIDTH, 0, 0 );							// Move To The Right Of The Character
			glEndList();										// Done Building The Display List
		}														// Loop Until All 256 Are Built
	}

	GLvoid Lesson39::KillFont( GLvoid )											// Delete The Font
	{
		glDeleteLists( base, 256 );									// Delete All 256 Characters
	}

	GLvoid Lesson39::glPrint( float x, float y, float z, const char* fmt, ... )	// Custom GL "Print" Routine
	{
		float		length = 0;										// Used To Find The Length Of The Text
		char		text[256];										// Holds Our String
		va_list		ap;												// Pointer To List Of Arguments

		if ( fmt == NULL )											// If There's No Text
			return;													// Do Nothing

		va_start( ap, fmt );											// Parses The String For Variables
		vsprintf_s( text, fmt, ap );								// And Converts Symbols To Actual Numbers
		va_end( ap );
		// Results Are Stored In Text
		length = (float)strlen( text );
		glPushMatrix();
		glEnable( GL_TEXTURE_2D );								// Enable Texture Mapping
		glEnable( GL_BLEND );
		glBlendFunc( GL_ONE, GL_ONE );
		glTranslated( x, y, z );									// Position The Text (0,0 - Bottom Left)
		glListBase( base - 32 );							// Choose The Font Set (0 or 1)

		glScalef( 0.05f * 0.8f, 0.05f, 1.0f );							// Enlarge Font Width And Height
		glTranslatef( -length * (float)GLYPH_WIDTH, 0.f, 0.f );
		glCallLists( (GLsizei)length, GL_UNSIGNED_BYTE, text );		// Write The Text To The Screen
		glDisable( GL_TEXTURE_2D );								// Disable Texture Mapping
		glDisable( GL_BLEND );
		glPopMatrix();
	}

	int Lesson39::InitGL( GLvoid )					// Any GL Init Code & User Initialiazation Goes Here
	{
		glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );						// Black Background
		glShadeModel( GL_SMOOTH );									// Select Smooth Shading
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );			// Set Perspective Calculations To Most Accurate

		BuildFont();											// Build The Font

		return TRUE;												// Return TRUE (Initialization Successful)
	}

	int Lesson39::CleanGL( GLvoid )										// Any User DeInitialization Goes Here
	{
		KillFont();

		constantVelocity->release();
		delete(constantVelocity);
		constantVelocity = NULL;

		motionUnderGravitation->release();
		delete(motionUnderGravitation);
		motionUnderGravitation = NULL;

		massConnectedWithSpring->release();
		delete(massConnectedWithSpring);
		massConnectedWithSpring = NULL;

		return TRUE;
	}

	void Lesson39::Update( DWORD milliseconds, bool keys[] )								// Perform Motion Updates Here
	{
		if ( keys[VK_F2] == TRUE )						// Is F2 Being Pressed?
			slowMotionRatio = 1.0f;									// Set slowMotionRatio To 1.0f (Normal Motion)

		if ( keys[VK_F3] == TRUE )						// Is F3 Being Pressed?
			slowMotionRatio = 10.0f;								// Set slowMotionRatio To 10.0f (Very Slow Motion)

		// dt Is The Time Interval (As Seconds) From The Previous Frame To The Current Frame.
		// dt Will Be Used To Iterate Simulation Values Such As Velocity And Position Of Masses.

		float dt = milliseconds / 1000.0f;							// Let's Convert Milliseconds To Seconds

		dt /= slowMotionRatio;										// Divide dt By slowMotionRatio And Obtain The New dt

		timeElapsed += dt;											// Iterate Elapsed Time

		float maxPossible_dt = 0.1f;								// Say That The Maximum Possible dt Is 0.1 Seconds
																	// This Is Needed So We Do Not Pass Over A Non Precise dt Value

		int numOfIterations = (int)(dt / maxPossible_dt) + 1;		// Calculate Number Of Iterations To Be Made At This Update Depending On maxPossible_dt And dt
		if ( numOfIterations != 0 )									// Avoid Division By Zero
			dt = dt / numOfIterations;								// dt Should Be Updated According To numOfIterations

		for ( int a = 0; a < numOfIterations; ++a )					// We Need To Iterate Simulations "numOfIterations" Times
		{
			constantVelocity->operate( dt );							// Iterate constantVelocity Simulation By dt Seconds
			motionUnderGravitation->operate( dt );					// Iterate motionUnderGravitation Simulation By dt Seconds
			massConnectedWithSpring->operate( dt );					// Iterate massConnectedWithSpring Simulation By dt Seconds
		}

	}

	int Lesson39::DrawGLScene( GLvoid )
	{
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();											// Reset The Modelview Matrix

		// Position Camera 40 Meters Up In Z-Direction.
		// Set The Up Vector In Y-Direction So That +X Directs To Right And +Y Directs To Up On The Window.
		gluLookAt( 0, 0, 40, 0, 0, 0, 0, 1, 0 );

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );		// Clear Screen And Depth Buffer


		// Drawing The Coordinate Plane Starts Here.
		// We Will Draw Horizontal And Vertical Lines With A Space Of 1 Meter Between Them.
		glColor3ub( 0, 0, 255 );										// Draw In Blue
		glBegin( GL_LINES );

		// Draw The Vertical Lines
		for ( float x = -20; x <= 20; x += 1.0f )						// x += 1.0f Stands For 1 Meter Of Space In This Example
		{
			glVertex3f( x, 20, 0 );
			glVertex3f( x, -20, 0 );
		}

		// Draw The Horizontal Lines
		for ( float y = -20; y <= 20; y += 1.0f )						// y += 1.0f Stands For 1 Meter Of Space In This Example
		{
			glVertex3f( 20, y, 0 );
			glVertex3f( -20, y, 0 );
		}

		glEnd();
		// Drawing The Coordinate Plane Ends Here.

		// Draw All Masses In constantVelocity Simulation (Actually There Is Only One Mass In This Example Of Code)
		glColor3ub( 255, 0, 0 );										// Draw In Red
		int a;
		for ( a = 0; a < constantVelocity->numOfMasses; ++a )
		{
			Mass* mass = constantVelocity->getMass( a );
			Vector3D* pos = &mass->pos;

			glPrint( pos->x, pos->y + 1, pos->z, "Mass with constant vel" );

			glPointSize( 4 );
			glBegin( GL_POINTS );
			glVertex3f( pos->x, pos->y, pos->z );
			glEnd();
		}
		// Drawing Masses In constantVelocity Simulation Ends Here.

		// Draw All Masses In motionUnderGravitation Simulation (Actually There Is Only One Mass In This Example Of Code)
		glColor3ub( 255, 255, 0 );									// Draw In Yellow
		for ( a = 0; a < motionUnderGravitation->numOfMasses; ++a )
		{
			Mass* mass = motionUnderGravitation->getMass( a );
			Vector3D* pos = &mass->pos;

			glPrint( pos->x, pos->y + 1, pos->z, "Motion under gravitation" );

			glPointSize( 4 );
			glBegin( GL_POINTS );
			glVertex3f( pos->x, pos->y, pos->z );
			glEnd();
		}
		// Drawing Masses In motionUnderGravitation Simulation Ends Here.

		// Draw All Masses In massConnectedWithSpring Simulation (Actually There Is Only One Mass In This Example Of Code)
		glColor3ub( 0, 255, 0 );										// Draw In Green
		for ( a = 0; a < massConnectedWithSpring->numOfMasses; ++a )
		{
			Mass* mass = massConnectedWithSpring->getMass( a );
			Vector3D* pos = &mass->pos;

			glPrint( pos->x, pos->y + 1, pos->z, "Mass connected with spring" );

			glPointSize( 8 );
			glBegin( GL_POINTS );
			glVertex3f( pos->x, pos->y, pos->z );
			glEnd();

			// Draw A Line From The Mass Position To Connection Position To Represent The Spring
			glBegin( GL_LINES );
			glVertex3f( pos->x, pos->y, pos->z );
			pos = &massConnectedWithSpring->connectionPos;
			glVertex3f( pos->x, pos->y, pos->z );
			glEnd();
		}
		// Drawing Masses In massConnectedWithSpring Simulation Ends Here.


		glColor3ub( 255, 255, 255 );									// Draw In White
		glPrint( -5.0f, 14, 0, "Time elapsed (seconds): %.2f", timeElapsed );	// Print timeElapsed
		glPrint( -5.0f, 13, 0, "Slow motion ratio: %.2f", slowMotionRatio );	// Print slowMotionRatio
		glPrint( -5.0f, 12, 0, "Press F2 for normal motion" );
		glPrint( -5.0f, 11, 0, "Press F3 for slow motion" );
		glBegin( GL_POINTS );
		glEnd();
		glFlush();													// Flush The GL Rendering Pipeline
		return TRUE;
	}
}