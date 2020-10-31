#include "framework.h"
#include "Lesson42.h"

namespace NeHe
{
	Lesson42::Lesson42()
	{
	}

	Lesson42::~Lesson42()
	{
	}

	void Lesson42::UpdateTex( int dmx, int dmy )										// Update Pixel dmx, dmy On The Texture
	{
		tex_data[0 + ((dmx + (width * dmy)) * 3)] = 255;								// Set Red Pixel To Full Bright
		tex_data[1 + ((dmx + (width * dmy)) * 3)] = 255;								// Set Green Pixel To Full Bright
		tex_data[2 + ((dmx + (width * dmy)) * 3)] = 255;								// Set Blue Pixel To Full Bright
	}

	void Lesson42::Reset( void )														// Reset The Maze, Colors, Start Point, Etc
	{
		ZeroMemory( tex_data, width * height * 3 );							// Clear Out The Texture Memory With 0's

#pragma warning( disable : 28159 )
		srand( GetTickCount() );												// Try To Get More Randomness
#pragma warning( default : 28159 )

		for ( int loop = 0; loop < 4; loop++ )									// Loop So We Can Assign 4 Random Colors
		{
			r[loop] = rand() % 128 + 128;											// Pick A Random Red Color (Bright)
			g[loop] = rand() % 128 + 128;											// Pick A Random Green Color (Bright)
			b[loop] = rand() % 128 + 128;											// Pick A Random Blue Color (Bright)
		}

		mx = int( rand() % (width / 2) ) * 2;											// Pick A New Random X Position
		my = int( rand() % (height / 2) ) * 2;										// Pick A New Random Y Position
	}

	int Lesson42::InitGL( GLvoid )							// Any GL Init Code & User Initialiazation Goes Here
	{
		tex_data = new BYTE[width * height * 3];									// Allocate Space For Our Texture

		Reset();															// Call Reset To Build Our Initial Texture, Etc.

		// Start Of User Initialization
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_data );

		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );								// Black Background
		glClearDepth( 1.0f );												// Depth Buffer Setup

		glDepthFunc( GL_LEQUAL );											// The Type Of Depth Testing
		glEnable( GL_DEPTH_TEST );											// Enable Depth Testing

		glEnable( GL_COLOR_MATERIAL );										// Enable Color Material (Allows Us To Tint Textures)

		glEnable( GL_TEXTURE_2D );											// Enable Texture Mapping

		quadric = gluNewQuadric();											// Create A Pointer To The Quadric Object
		gluQuadricNormals( quadric, GLU_SMOOTH );								// Create Smooth Normals 
		gluQuadricTexture( quadric, GL_TRUE );								// Create Texture Coords

		glEnable( GL_LIGHT0 );												// Enable Light0 (Default GL Light)

		return TRUE;														// Return TRUE (Initialization Successful)
	}

	int Lesson42::CleanGL( GLvoid ) 												// Any User DeInitialization Goes Here
	{
		delete[] tex_data;													// Delete Our Texture Data (Freeing Up Memory)
		return TRUE;
	}

	const char* Lesson42::GetDescription() const
	{
		return "Space - Reset";
	}

	void Lesson42::Update( DWORD milliseconds, bool keys[] )										// Perform Motion Updates Here
	{
		int		dir;														// Will Hold Current Direction

		if ( keys[' '] && !sp )									// Check To See If Spacebar Is Pressed
		{
			sp = TRUE;														// If So, Set sp To TRUE (Spacebar Pressed)
			Reset();														// If So, Call Reset And Start A New Maze
		}

		if ( !keys[' '] )											// Check To See If Spacebar Has Been Released
			sp = FALSE;														// If So, Set sp To FALSE (Spacebar Released)

		xrot += (float)(milliseconds) * 0.02f;									// Increase Rotation On The X-Axis
		yrot += (float)(milliseconds) * 0.03f;									// Increase Rotation On The Y-Axis
		zrot += (float)(milliseconds) * 0.015f;									// Increase Rotation On The Z-Axis

		done = TRUE;															// Set done To True
		for ( int x = 0; x < width; x += 2 )										// Loop Through All The Rooms
		{
			for ( int y = 0; y < height; y += 2 )									// On X And Y Axis
			{
				if ( tex_data[((x + (width * y)) * 3)] == 0 )							// If Current Texture Pixel (Room) Is Blank
					done = FALSE;												// We Have To Set done To False (Not Finished Yet)
			}
		}

		//if ( done )															// If done Is True Then There Were No Unvisited Rooms
		//{
		//	// Display A Message At The Top Of The Window, Pause For A Bit And Then Start Building A New Maze!
		//	SetWindowText( g_window->hWnd, "Lesson 42: Multiple Viewports... 2003 NeHe Productions... Maze Complete!" );
		//	Sleep( 5000 );
		//	SetWindowText( g_window->hWnd, "Lesson 42: Multiple Viewports... 2003 NeHe Productions... Building Maze!" );
		//	Reset();
		//}

		// Check To Make Sure We Are Not Trapped (Nowhere Else To Move)
		if ( ((mx > (width - 4) || tex_data[(((mx + 2) + (width * my)) * 3)] == 255)) && ((mx < 2 || tex_data[(((mx - 2) + (width * my)) * 3)] == 255)) &&
			((my > ( height - 4 ) || tex_data[((mx + (width * (my + 2))) * 3)] == 255)) && ((my < 2 || tex_data[((mx + (width * (my - 2))) * 3)] == 255)) )
		{
			do																// If We Are Trapped
			{
				mx = int( rand() % (width / 2) ) * 2;									// Pick A New Random X Position
				my = int( rand() % (height / 2) ) * 2;								// Pick A New Random Y Position
			} while ( tex_data[((mx + (width * my)) * 3)] == 0 );						// Keep Picking A Random Position Until We Find
		}																	// One That Has Already Been Tagged (Safe Starting Point)

		dir = int( rand() % 4 );													// Pick A Random Direction

		if ( (dir == 0) && (mx <= (width - 4)) )									// If The Direction Is 0 (Right) And We Are Not At The Far Right
		{
			if ( tex_data[(((mx + 2) + (width * my)) * 3)] == 0 )						// And If The Room To The Right Has Not Already Been Visited
			{
				UpdateTex( mx + 1, my );											// Update The Texture To Show Path Cut Out Between Rooms
				mx += 2;														// Move To The Right (Room To The Right)
			}
		}

		if ( (dir == 1) && (my <= (height - 4)) )									// If The Direction Is 1 (Down) And We Are Not At The Bottom
		{
			if ( tex_data[((mx + (width * (my + 2))) * 3)] == 0 )						// And If The Room Below Has Not Already Been Visited
			{
				UpdateTex( mx, my + 1 );											// Update The Texture To Show Path Cut Out Between Rooms
				my += 2;														// Move Down (Room Below)
			}
		}

		if ( (dir == 2) && (mx >= 2) )											// If The Direction Is 2 (Left) And We Are Not At The Far Left
		{
			if ( tex_data[(((mx - 2) + (width * my)) * 3)] == 0 )						// And If The Room To The Left Has Not Already Been Visited
			{
				UpdateTex( mx - 1, my );											// Update The Texture To Show Path Cut Out Between Rooms
				mx -= 2;														// Move To The Left (Room To The Left)
			}
		}

		if ( (dir == 3) && (my >= 2) )											// If The Direction Is 3 (Up) And We Are Not At The Top
		{
			if ( tex_data[((mx + (width * (my - 2))) * 3)] == 0 )						// And If The Room Above Has Not Already Been Visited
			{
				UpdateTex( mx, my - 1 );											// Update The Texture To Show Path Cut Out Between Rooms
				my -= 2;														// Move Up (Room Above)
			}
		}

		UpdateTex( mx, my );													// Update Current Room
	}

	GLvoid Lesson42::ReSizeGLScene( GLsizei width, GLsizei height )
	{
		ILesson::ReSizeGLScene( width, height );
		rect = RECT{ 0, 0, width, height };
	}

	int Lesson42::DrawGLScene( GLvoid )														// Our Drawing Routine
	{
		int window_width = rect.right - rect.left;								// Calculate The Width (Right Side-Left Side)
		int window_height = rect.bottom - rect.top;								// Calculate The Height (Bottom-Top)

		// Update Our Texture... This Is The Key To The Programs Speed... Much Faster Than Rebuilding The Texture Each Time
		glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, tex_data );

		glClear( GL_COLOR_BUFFER_BIT );										// Clear Screen

		for ( int loop = 0; loop < 4; loop++ )									// Loop To Draw Our 4 Views
		{
			glColor3ub( r[loop], g[loop], b[loop] );							// Assign Color To Current View

			if ( loop == 0 )													// If We Are Drawing The First Scene
			{
				// Set The Viewport To The Top Left.  It Will Take Up Half The Screen Width And Height
				glViewport( 0, window_height / 2, window_width / 2, window_height / 2 );
				glMatrixMode( GL_PROJECTION );								// Select The Projection Matrix
				glLoadIdentity();											// Reset The Projection Matrix
				// Set Up Ortho Mode To Fit 1/4 The Screen (Size Of A Viewport)
				gluOrtho2D( 0, window_width / 2, window_height / 2, 0 );
			}

			if ( loop == 1 )													// If We Are Drawing The Second Scene
			{
				// Set The Viewport To The Top Right.  It Will Take Up Half The Screen Width And Height
				glViewport( window_width / 2, window_height / 2, window_width / 2, window_height / 2 );
				glMatrixMode( GL_PROJECTION );								// Select The Projection Matrix
				glLoadIdentity();											// Reset The Projection Matrix
				// Set Up Perspective Mode To Fit 1/4 The Screen (Size Of A Viewport)
				gluPerspective( 45.0, (GLfloat)(width) / (GLfloat)(height), 0.1f, 500.0 );
			}

			if ( loop == 2 )													// If We Are Drawing The Third Scene
			{
				// Set The Viewport To The Bottom Right.  It Will Take Up Half The Screen Width And Height
				glViewport( window_width / 2, 0, window_width / 2, window_height / 2 );
				glMatrixMode( GL_PROJECTION );								// Select The Projection Matrix
				glLoadIdentity();											// Reset The Projection Matrix
				// Set Up Perspective Mode To Fit 1/4 The Screen (Size Of A Viewport)
				gluPerspective( 45.0, (GLfloat)(width) / (GLfloat)(height), 0.1f, 500.0 );
			}

			if ( loop == 3 )													// If We Are Drawing The Fourth Scene
			{
				// Set The Viewport To The Bottom Left.  It Will Take Up Half The Screen Width And Height
				glViewport( 0, 0, window_width / 2, window_height / 2 );
				glMatrixMode( GL_PROJECTION );								// Select The Projection Matrix
				glLoadIdentity();											// Reset The Projection Matrix
				// Set Up Perspective Mode To Fit 1/4 The Screen (Size Of A Viewport)
				gluPerspective( 45.0, (GLfloat)(width) / (GLfloat)(height), 0.1f, 500.0 );
			}

			glMatrixMode( GL_MODELVIEW );									// Select The Modelview Matrix
			glLoadIdentity();												// Reset The Modelview Matrix

			glClear( GL_DEPTH_BUFFER_BIT );									// Clear Depth Buffer

			if ( loop == 0 )													// Are We Drawing The First Image?  (Original Texture... Ortho)
			{
				glBegin( GL_QUADS );											// Begin Drawing A Single Quad
					// We Fill The Entire 1/4 Section With A Single Textured Quad.
				glTexCoord2f( 1.0f, 0.0f ); glVertex2i( window_width / 2, 0 );
				glTexCoord2f( 0.0f, 0.0f ); glVertex2i( 0, 0 );
				glTexCoord2f( 0.0f, 1.0f ); glVertex2i( 0, window_height / 2 );
				glTexCoord2f( 1.0f, 1.0f ); glVertex2i( window_width / 2, window_height / 2 );
				glEnd();													// Done Drawing The Textured Quad
			}

			if ( loop == 1 )													// Are We Drawing The Second Image?  (3D Texture Mapped Sphere... Perspective)
			{
				glTranslatef( 0.0f, 0.0f, -14.0f );								// Move 14 Units Into The Screen

				glRotatef( xrot, 1.0f, 0.0f, 0.0f );								// Rotate By xrot On The X-Axis
				glRotatef( yrot, 0.0f, 1.0f, 0.0f );								// Rotate By yrot On The Y-Axis
				glRotatef( zrot, 0.0f, 0.0f, 1.0f );								// Rotate By zrot On The Z-Axis

				glEnable( GL_LIGHTING );										// Enable Lighting
				gluSphere( quadric, 4.0f, 32, 32 );								// Draw A Sphere
				glDisable( GL_LIGHTING );										// Disable Lighting
			}

			if ( loop == 2 )													// Are We Drawing The Third Image?  (Texture At An Angle... Perspective)
			{
				glTranslatef( 0.0f, 0.0f, -2.0f );								// Move 2 Units Into The Screen
				glRotatef( -45.0f, 1.0f, 0.0f, 0.0f );							// Tilt The Quad Below Back 45 Degrees.
				glRotatef( zrot / 1.5f, 0.0f, 0.0f, 1.0f );						// Rotate By zrot/1.5 On The Z-Axis

				glBegin( GL_QUADS );											// Begin Drawing A Single Quad
				glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, 0.0f );
				glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, 0.0f );
				glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 0.0f );
				glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, 0.0f );
				glEnd();													// Done Drawing The Textured Quad
			}

			if ( loop == 3 )													// Are We Drawing The Fourth Image?  (3D Texture Mapped Cylinder... Perspective)
			{
				glTranslatef( 0.0f, 0.0f, -7.0f );								// Move 7 Units Into The Screen
				glRotatef( -xrot / 2, 1.0f, 0.0f, 0.0f );							// Rotate By -xrot/2 On The X-Axis
				glRotatef( -yrot / 2, 0.0f, 1.0f, 0.0f );							// Rotate By -yrot/2 On The Y-Axis
				glRotatef( -zrot / 2, 0.0f, 0.0f, 1.0f );							// Rotate By -zrot/2 On The Z-Axis

				glEnable( GL_LIGHTING );										// Enable Lighting
				glTranslatef( 0.0f, 0.0f, -2.0f );								// Translate -2 On The Z-Axis (To Rotate Cylinder Around The Center, Not An End)
				gluCylinder( quadric, 1.5f, 1.5f, 4.0f, 32, 16 );					// Draw A Cylinder
				glDisable( GL_LIGHTING );										// Disable Lighting
			}
		}

		glFlush();															// Flush The GL Rendering Pipeline
		return TRUE;
	}
}