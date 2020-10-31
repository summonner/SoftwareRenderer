#include "framework.h"
#include "Lesson44.h"

namespace NeHe
{
	Lesson44::Lesson44()
	{
	}

	Lesson44::~Lesson44()
	{
	}

	bool Lesson44::LoadTexture( LPCSTR szFileName, GLuint& texid )					// Creates Texture From A Bitmap File
	{
		HBITMAP hBMP;													// Handle Of The Bitmap
		BITMAP	BMP;													// Bitmap Structure

		glGenTextures( 1, &texid );										// Create The Texture
		hBMP = (HBITMAP)LoadImage( GetModuleHandle( NULL ), CA2CT(szFileName), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );

		if ( !hBMP )														// Does The Bitmap Exist?
			return FALSE;												// If Not Return False

		GetObject( hBMP, sizeof( BMP ), &BMP );								// Get The Object
																		// hBMP:        Handle To Graphics Object
																		// sizeof(BMP): Size Of Buffer For Object Information
																		// &BMP:        Buffer For Object Information

		glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );							// Pixel Storage Mode (Word Alignment / 4 Bytes)

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture( GL_TEXTURE_2D, texid );								// Bind To The Texture ID
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );	// Linear Min Filter
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );	// Linear Mag Filter
		glTexImage2D( GL_TEXTURE_2D, 0, 3, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits );

		DeleteObject( hBMP );												// Delete The Object

		return TRUE;													// Loading Was Successful
	}

	GLvoid Lesson44::ReSizeGLScene( GLsizei width, GLsizei height )					// Resize And Initialize The GL Window
	{
		gCamera.m_WindowHeight = height;								// The camera needs to know the window height
		gCamera.m_WindowWidth = width;									// The camera needs to know the window width

		if ( height == 0 )													// Prevent A Divide By Zero By
		{
			height = 1;													// Making Height Equal One
		}

		glViewport( 0, 0, width, height );									// Reset The Current Viewport

		glMatrixMode( GL_PROJECTION );									// Select The Projection Matrix
		glLoadIdentity();												// Reset The Projection Matrix

		// Calculate The Aspect Ratio Of The Window
		gluPerspective( 45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f );

		glMatrixMode( GL_MODELVIEW );										// Select The Modelview Matrix
		glLoadIdentity();												// Reset The Modelview Matrix
	}

	int Lesson44::InitGL( GLvoid )													// All Setup For OpenGL Goes Here
	{
		GLuint tex = 0;

		glShadeModel( GL_SMOOTH );										// Enable Smooth Shading
		glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );							// Black Background
		glClearDepth( 1.0f );												// Depth Buffer Setup
		glEnable( GL_DEPTH_TEST );										// Enables Depth Testing
		glDepthFunc( GL_LEQUAL );											// The Type Of Depth Testing To Do
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );				// Really Nice Perspective Calculations

		LoadTexture( "Art/Font.bmp", tex );								// Load the font texture
		if ( tex != 0 )													// Make sure it was loaded
		{
			gFont.SetFontTexture( tex );									// Set the font texture
			gFont.SetWindowSize( 1024, 768 );								// The font class needs to know the window size
			gFont.BuildFont( 1.0f );					                    // Build the font
		}
		else
		{
			MessageBox( NULL,											// We didn't load the font texture
				_T("Failed to load font texture."),					// so tell the user about it.
				_T("Error"),
				MB_OK );
		}

		gCamera.m_MaxHeadingRate = 1.0f;								// Set our Maximum rates for the camera
		gCamera.m_MaxPitchRate = 1.0f;									// Set our Maximum rates for the camera
		gCamera.m_HeadingDegrees = 0.0f;								// Set our Maximum rates for the camera

		// Try and load the HardGlow texture tell the user if we can't find it then quit
		LoadTexture( "Art/HardGlow2.bmp", gCamera.m_GlowTexture );
		if ( gCamera.m_GlowTexture == 0 )
		{
			MessageBox( NULL, _T("Failed to load Hard Glow texture."), _T("Error"), MB_OK );
			return(FALSE);
		}

		// Try and load the BigGlow texture tell the user if we can't find it then quit
		LoadTexture( "Art/BigGlow3.bmp", gCamera.m_BigGlowTexture );
		if ( gCamera.m_BigGlowTexture == 0 )
		{
			MessageBox( NULL, _T("Failed to load Big Glow texture."), _T("Error"), MB_OK );
			return(FALSE);
		}

		// Try and load the Halo texture tell the user if we can't find it then quit
		LoadTexture( "Art/Halo3.bmp", gCamera.m_HaloTexture );
		if ( gCamera.m_HaloTexture == 0 )
		{
			MessageBox( NULL, _T("Failed to load Halo texture."), _T("Error"), MB_OK );
			return(FALSE);
		}

		// Try and load the Streaks texture tell the user if we can't find it then quit
		LoadTexture( "Art/Streaks4.bmp", gCamera.m_StreakTexture );
		if ( gCamera.m_StreakTexture == 0 )
		{
			MessageBox( NULL, _T("Failed to load Streaks texture."), _T("Error"), MB_OK );
			return(FALSE);
		}

		//##################  NEW STUFF  ##################################

			// Just create a cylinder that will be used as occluder object
		cylList = glGenLists( 1 );
		qobj = gluNewQuadric();
		gluQuadricDrawStyle( qobj, GLU_FILL );
		gluQuadricNormals( qobj, GLU_SMOOTH );
		glNewList( cylList, GL_COMPILE );
		glEnable( GL_COLOR_MATERIAL );
		glColor3f( 0.0f, 0.0f, 1.0f );
		glEnable( GL_LIGHT0 );
		glEnable( GL_LIGHTING );
		glTranslatef( 0.0f, 0.0f, -2.0f );
		gluCylinder( qobj, 0.5, 0.5, 4.0, 15, 5 );
		glDisable( GL_LIGHTING );
		glDisable( GL_LIGHT0 );
		glDisable( GL_COLOR_MATERIAL );
		glEndList();

		gStartTime = timeGetTime();										// Get the time the app started

		return TRUE;													// Initialization Went OK
	}

	int Lesson44::DrawGLScene( GLvoid )												// Here's Where We Do All The Drawing
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );				// Clear Screen And Depth Buffer
		glLoadIdentity();												// Reset The Current Modelview Matrix

		// We want our light source to be 50 units if front 
		// of the camera all the time to make it look like 
		// it is infinately far away from the camera. We only
		// do this to the z coordinate because we want to see
		// the flares adjust if we fly in a straight line.
		gCamera.m_LightSourcePos.z = gCamera.m_Position.z - 50.0f;

		//##################### NEW STUFF ##########################
		// Draw our cylinder and make it "do something"
		// Of course we do that BEFORE testing for occlusion
		// We need our depth buffer to be filled to check against occluder objects
		glPushMatrix();
		glLoadIdentity();
		glTranslatef( 0.0f, 0.0f, -20.0f );
		glRotatef( timeGetTime() / 50.0f, 0.3f, 0.0f, 0.0f );
		glRotatef( timeGetTime() / 50.0f, 0.0f, 0.5f, 0.0f );
		glCallList( cylList );
		glPopMatrix();

		gCamera.SetPrespective();										// Set our perspective/oriention on the world
		gCamera.RenderLensFlare();										// Render the lens flare
		gCamera.UpdateFrustumFaster();									// Update the frustum as fast as possible.

		if ( infoOn == TRUE )
		{											// Check to see if info has been toggled by 1,2
			DrawGLInfo();												// Info is on so draw the GL information.								
		}

		return TRUE;
	}

	int Lesson44::CleanGL( GLvoid )
	{
		// This code is missing a proper unload function  ;D
		gluDeleteQuadric( qobj );							// Delete our quadric object
		glDeleteLists( cylList, 1 );						// Delete the cylinder list
		return TRUE;
	}

	void Lesson44::DrawGLInfo( void )
	{
		GLfloat modelMatrix[16];									// This will hold the model view matrix
		GLfloat projMatrix[16];										// This will hold the projection matrix
		GLfloat DiffTime;											// This is will contain the difference in time
		char String[64];											// A temporary string to use to format information
																	// that will be printed to the screen.

		glGetFloatv( GL_PROJECTION_MATRIX, projMatrix );				// Grab the projection matrix
		glGetFloatv( GL_MODELVIEW_MATRIX, modelMatrix );				// Grab the modelview matrix

		// Print out the cameras position
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
		sprintf_s( String, "m_Position............. = %.02f, %.02f, %.02f", gCamera.m_Position.x, gCamera.m_Position.y, gCamera.m_Position.z );
		gFont.glPrintf( 10, 720, 1, String );

		// Print out the cameras direction
		sprintf_s( String, "m_DirectionVector...... = %.02f, %.02f, %.02f", gCamera.m_DirectionVector.i, gCamera.m_DirectionVector.j, gCamera.m_DirectionVector.k );
		gFont.glPrintf( 10, 700, 1, String );

		// Print out the light sources position
		sprintf_s( String, "m_LightSourcePos....... = %.02f, %.02f, %.02f", gCamera.m_LightSourcePos.x, gCamera.m_LightSourcePos.y, gCamera.m_LightSourcePos.z );
		gFont.glPrintf( 10, 680, 1, String );

		// Print out the intersection point
		sprintf_s( String, "ptIntersect............ = %.02f, %.02f, %.02f", gCamera.ptIntersect.x, gCamera.ptIntersect.y, gCamera.ptIntersect.x );
		gFont.glPrintf( 10, 660, 1, String );

		// Print out the vector that points from the light source to the camera
		sprintf_s( String, "vLightSourceToCamera... = %.02f, %.02f, %.02f", gCamera.vLightSourceToCamera.i, gCamera.vLightSourceToCamera.j, gCamera.vLightSourceToCamera.k );
		gFont.glPrintf( 10, 640, 1, String );

		// Print out the vector that points from the light source to the intersection point.
		sprintf_s( String, "vLightSourceToIntersect = %.02f, %.02f, %.02f", gCamera.vLightSourceToIntersect.i, gCamera.vLightSourceToIntersect.j, gCamera.vLightSourceToIntersect.k );
		gFont.glPrintf( 10, 620, 1, String );

		// Let everyone know the below matrix is the model view matrix
		sprintf_s( String, "GL_MODELVIEW_MATRIX" );
		gFont.glPrintf( 10, 580, 1, String );

		// Print out row 1 of the model view matrix
		sprintf_s( String, "%.02f, %.02f, %.02f, %.02f", modelMatrix[0], modelMatrix[1], modelMatrix[2], modelMatrix[3] );
		gFont.glPrintf( 10, 560, 1, String );

		// Print out row 2 of the model view matrix
		sprintf_s( String, "%.02f, %.02f, %.02f, %.02f", modelMatrix[4], modelMatrix[5], modelMatrix[6], modelMatrix[7] );
		gFont.glPrintf( 10, 540, 1, String );

		// Print out row 3 of the model view matrix
		sprintf_s( String, "%.02f, %.02f, %.02f, %.02f", modelMatrix[8], modelMatrix[9], modelMatrix[10], modelMatrix[11] );
		gFont.glPrintf( 10, 520, 1, String );

		// Print out row 4 of the model view matrix
		sprintf_s( String, "%.02f, %.02f, %.02f, %.02f", modelMatrix[12], modelMatrix[13], modelMatrix[14], modelMatrix[15] );
		gFont.glPrintf( 10, 500, 1, String );

		// Let everyone know the below matrix is the projection matrix
		sprintf_s( String, "GL_PROJECTION_MATRIX" );
		gFont.glPrintf( 10, 460, 1, String );

		// Print out row 1 of the projection view matrix
		sprintf_s( String, "%.02f, %.02f, %.02f, %.02f", projMatrix[0], projMatrix[1], projMatrix[2], projMatrix[3] );
		gFont.glPrintf( 10, 440, 1, String );

		// Print out row 2 of the projection view matrix
		sprintf_s( String, "%.02f, %.02f, %.02f, %.02f", projMatrix[4], projMatrix[5], projMatrix[6], projMatrix[7] );
		gFont.glPrintf( 10, 420, 1, String );

		// Print out row 3 of the projection view matrix
		sprintf_s( String, "%.02f, %.02f, %.03f, %.03f", projMatrix[8], projMatrix[9], projMatrix[10], projMatrix[11] );
		gFont.glPrintf( 10, 400, 1, String );

		// Print out row 4 of the projection view matrix
		sprintf_s( String, "%.02f, %.02f, %.03f, %.03f", projMatrix[12], projMatrix[13], projMatrix[14], projMatrix[15] );
		gFont.glPrintf( 10, 380, 1, String );

		// Let everyone know the below values are the Frustum clipping planes
		gFont.glPrintf( 10, 320, 1, "FRUSTUM CLIPPING PLANES" );

		// Print out the right clipping plane
		sprintf_s( String, "%.02f, %.02f, %.02f, %.02f", gCamera.m_Frustum[0][0], gCamera.m_Frustum[0][1], gCamera.m_Frustum[0][2], gCamera.m_Frustum[0][3] );
		gFont.glPrintf( 10, 300, 1, String );

		// Print out the left clipping plane
		sprintf_s( String, "%.02f, %.02f, %.02f, %.02f", gCamera.m_Frustum[1][0], gCamera.m_Frustum[1][1], gCamera.m_Frustum[1][2], gCamera.m_Frustum[1][3] );
		gFont.glPrintf( 10, 280, 1, String );

		// Print out the bottom clipping plane
		sprintf_s( String, "%.02f, %.02f, %.02f, %.02f", gCamera.m_Frustum[2][0], gCamera.m_Frustum[2][1], gCamera.m_Frustum[2][2], gCamera.m_Frustum[2][3] );
		gFont.glPrintf( 10, 260, 1, String );

		// Print out the top clipping plane
		sprintf_s( String, "%.02f, %.02f, %.02f, %.02f", gCamera.m_Frustum[3][0], gCamera.m_Frustum[3][1], gCamera.m_Frustum[3][2], gCamera.m_Frustum[3][3] );
		gFont.glPrintf( 10, 240, 1, String );

		// Print out the far clipping plane
		sprintf_s( String, "%.02f, %.02f, %.02f, %.02f", gCamera.m_Frustum[4][0], gCamera.m_Frustum[4][1], gCamera.m_Frustum[4][2], gCamera.m_Frustum[4][3] );
		gFont.glPrintf( 10, 220, 1, String );

		// Print out the near clipping plane
		sprintf_s( String, "%.02f, %.02f, %.02f, %.02f", gCamera.m_Frustum[5][0], gCamera.m_Frustum[5][1], gCamera.m_Frustum[5][2], gCamera.m_Frustum[5][3] );
		gFont.glPrintf( 10, 200, 1, String );

		if ( gFrames >= 100 )											// if we are due for another FPS update
		{
			gCurrentTime = timeGetTime();							// Get the current time
			DiffTime = GLfloat( gCurrentTime - gStartTime );			// Find the difference between the start and end times
			gFPS = (gFrames / DiffTime) * 1000.0f;					// Compute the FPS
			gStartTime = gCurrentTime;								// Set the current start time to the current time
			gFrames = 1;											// Set the number of frames to 1
		}
		else
		{
			gFrames++;												// We are not due to for another update so add one to the frame count
		}

		// Print out the FPS
		sprintf_s( String, "FPS %.02f", gFPS );
		gFont.glPrintf( 10, 160, 1, String );
	}

	const char* Lesson44::GetDescription() const
	{
		return "W/A/S/D - Rotate Camera\n\
				Z/X/C - Move Camera\n\
				1/2 - Toggle Info";
	}

	void Lesson44::Update( DWORD milliseconds, bool keys[] )
	{
		if ( keys['W'] == TRUE )										// Is the W key down?
		{
			gCamera.ChangePitch( -0.2f );								// Pitch the camera up 0.2 degrees
		}

		if ( keys['S'] == TRUE )										// Is the S key down?
		{
			gCamera.ChangePitch( 0.2f );								// Pitch the camera down 0.2 degrees
		}

		if ( keys['D'] == TRUE )										// Is the D key down?
		{
			gCamera.ChangeHeading( 0.2f );							// Yaw the camera to the left
		}

		if ( keys['A'] == TRUE )										// Is the A key down?
		{
			gCamera.ChangeHeading( -0.2f );							// Yaw the camera to the right
		}

		if ( keys['Z'] == TRUE )										// Is the Z key down?
		{
			gCamera.m_ForwardVelocity = 0.01f;						// Start moving the camera forward 0.01 units every frame
		}

		if ( keys['C'] == TRUE )										// Is the C key down?
		{
			gCamera.m_ForwardVelocity = -0.01f;						// Start moving the camera backwards 0.01 units every frame
		}

		if ( keys['X'] == TRUE )										// Is the X key down?
		{
			gCamera.m_ForwardVelocity = 0.0f;						// Stop the camera from moving.
		}

		if ( keys['1'] == TRUE )										// Is the 1 key down?
		{
			infoOn = TRUE;											// Toggle info on
		}

		if ( keys['2'] == TRUE )										// Is the 2 key down?
		{
			infoOn = FALSE;											// Toggle info off
		}
	}
}