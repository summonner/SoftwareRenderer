#include "framework.h"
#include "Lesson34.h"

namespace NeHe
{
	Lesson34::Lesson34()
		: g_HeightMap{ 0, }
	{
	}

	Lesson34::~Lesson34()
	{
	}

	GLvoid Lesson34::ReSizeGLScene( GLsizei width, GLsizei height )		// Resize And Initialize The GL Window
	{
		if ( height == 0 )										// Prevent A Divide By Zero By
			height = 1;										// Making Height Equal One

		glViewport( 0, 0, width, height );						// Reset The Current Viewport

		glMatrixMode( GL_PROJECTION );						// Select The Projection Matrix
		glLoadIdentity();									// Reset The Projection Matrix

		// Calculate The Aspect Ratio Of The Window.  Farthest Distance Changed To 500.0f (NEW)
		gluPerspective( 45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 500.0f );

		glMatrixMode( GL_MODELVIEW );							// Select The Modelview Matrix
		glLoadIdentity();									// Reset The Modelview Matrix
	}

	// Loads The .RAW File And Stores It In pHeightMap
	void Lesson34::LoadRawFile( LPCSTR strName, int nSize, BYTE* pHeightMap )
	{
		FILE* pFile = NULL;

		// Open The File In Read / Binary Mode.
		pFile = fopen( strName, "rb" );

		// Check To See If We Found The File And Could Open It
		if ( pFile == NULL )
		{
			// Display Error Message And Stop The Function
			MessageBox( NULL, _T( "Can't Find The Height Map!" ), _T( "Error" ), MB_OK );
			return;
		}

		fread( pHeightMap, 1, nSize, pFile );

		// After We Read The Data, It's A Good Idea To Check If Everything Read Fine
		int result = ferror( pFile );

		// Check If We Received An Error
		if ( result )
		{
			MessageBox( NULL, _T( "Failed To Get Data!" ), _T( "Error" ), MB_OK );
		}

		// Close The File.
		fclose( pFile );
	}

	int Lesson34::InitGL( GLvoid )										// All Setup For OpenGL Goes Here
	{
		glShadeModel( GL_SMOOTH );							// Enable Smooth Shading
		glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );				// Black Background
		glClearDepth( 1.0f );									// Depth Buffer Setup
		glEnable( GL_DEPTH_TEST );							// Enables Depth Testing
		glDepthFunc( GL_LEQUAL );								// The Type Of Depth Testing To Do
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );	// Really Nice Perspective Calculations

		LoadRawFile( "Data/Terrain.raw", MAP_SIZE * MAP_SIZE, g_HeightMap );	// (NEW)

		return TRUE;										// Initialization Went OK
	}


	int Height( BYTE* pHeightMap, int X, int Y )				// This Returns The Height From A Height Map Index
	{
		int x = X % MAP_SIZE;								// Error Check Our x Value
		int y = Y % MAP_SIZE;								// Error Check Our y Value

		if ( !pHeightMap ) return 0;							// Make Sure Our Data Is Valid

		return pHeightMap[x + (y * MAP_SIZE)];				// Index Into Our Height Array And Return The Height
	}

	void SetVertexColor( BYTE* pHeightMap, int x, int y )		// Sets The Color Value For A Particular Index, Depending On The Height Index
	{
		if ( !pHeightMap ) return;								// Make Sure Our Height Data Is Valid

		float fColor = -0.15f + (Height( pHeightMap, x, y ) / 256.0f);

		// Assign This Blue Shade To The Current Vertex
		glColor3f( 0, 0, fColor );
	}

	void Lesson34::RenderHeightMap( BYTE pHeightMap[] )					// This Renders The Height Map As Quads
	{
		int X = 0, Y = 0;									// Create Some Variables To Walk The Array With.
		int x, y, z;										// Create Some Variables For Readability

		if ( !pHeightMap ) return;								// Make Sure Our Height Data Is Valid

		if ( bRender )											// What We Want To Render
			glBegin( GL_QUADS );							// Render Polygons
		else
			glBegin( GL_LINES );							// Render Lines Instead

		for ( X = 0; X < (MAP_SIZE - STEP_SIZE); X += STEP_SIZE )
			for ( Y = 0; Y < (MAP_SIZE - STEP_SIZE); Y += STEP_SIZE )
			{
				// Get The (X, Y, Z) Value For The Bottom Left Vertex
				x = X;
				y = Height( pHeightMap, X, Y );
				z = Y;

				// Set The Color Value Of The Current Vertex
				SetVertexColor( pHeightMap, x, z );

				glVertex3i( x, y, z );						// Send This Vertex To OpenGL To Be Rendered (Integer Points Are Faster)

				// Get The (X, Y, Z) Value For The Top Left Vertex
				x = X;
				y = Height( pHeightMap, X, Y + STEP_SIZE );
				z = Y + STEP_SIZE;

				// Set The Color Value Of The Current Vertex
				SetVertexColor( pHeightMap, x, z );

				glVertex3i( x, y, z );						// Send This Vertex To OpenGL To Be Rendered

				// Get The (X, Y, Z) Value For The Top Right Vertex
				x = X + STEP_SIZE;
				y = Height( pHeightMap, X + STEP_SIZE, Y + STEP_SIZE );
				z = Y + STEP_SIZE;

				// Set The Color Value Of The Current Vertex
				SetVertexColor( pHeightMap, x, z );

				glVertex3i( x, y, z );						// Send This Vertex To OpenGL To Be Rendered

				// Get The (X, Y, Z) Value For The Bottom Right Vertex
				x = X + STEP_SIZE;
				y = Height( pHeightMap, X + STEP_SIZE, Y );
				z = Y;

				// Set The Color Value Of The Current Vertex
				SetVertexColor( pHeightMap, x, z );

				glVertex3i( x, y, z );						// Send This Vertex To OpenGL To Be Rendered
			}
		glEnd();

		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );					// Reset The Color
	}

	int Lesson34::DrawGLScene( GLvoid )									// Here's Where We Do All The Drawing
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// Clear The Screen And The Depth Buffer
		glLoadIdentity();									// Reset The Matrix

		// 			 Position	      View		Up Vector
		gluLookAt( 212, 60, 194, 186, 55, 171, 0, 1, 0 );	// This Determines Where The Camera's Position And View Is

		glScalef( scaleValue, scaleValue * HEIGHT_RATIO, scaleValue );

		RenderHeightMap( g_HeightMap );						// Render The Height Map

		return TRUE;										// Keep Going
	}

	void Lesson34::Update( DWORD milliseconds, bool keys[] )
	{
		if ( keys[VK_UP] )							// Is the UP ARROW key Being Pressed?
			scaleValue += 0.001f;					// Increase the scale value to zoom in

		if ( keys[VK_DOWN] )							// Is the DOWN ARROW key Being Pressed?
			scaleValue -= 0.001f;					// Decrease the scale value to zoom out
	}

	const char* Lesson34::GetDescription() const
	{
		return "Up/Down - Zoom\n\
				LButton - Toggle Render Mode";
	}

	void Lesson34::OnMove( int x, int y )
	{
		// do nothing
	}

	void Lesson34::OnLButton( bool isPressed )
	{
		if ( isPressed == false )
		{
			return;
		}

		bRender = !bRender;
	}
}