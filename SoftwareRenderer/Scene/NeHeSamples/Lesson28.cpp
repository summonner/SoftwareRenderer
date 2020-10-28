#include "framework.h"
#include "Lesson28.h"

namespace NeHe
{
	Lesson28::Lesson28()
		: mybezier()
	{
	}

	Lesson28::~Lesson28()
	{
	}
	
	// Adds 2 points. Don't just use '+' ;)
	Lesson28::POINT_3D Lesson28::pointAdd( POINT_3D p, POINT_3D q )
	{
		p.x += q.x;		p.y += q.y;		p.z += q.z;
		return p;
	}

	// Multiplies a point and a constant. Don't just use '*'
	Lesson28::POINT_3D Lesson28::pointTimes( double c, POINT_3D p )
	{
		p.x *= c;	p.y *= c;	p.z *= c;
		return p;
	}

	// Function for quick point creation
	Lesson28::POINT_3D Lesson28::makePoint( double a, double b, double c )
	{
		POINT_3D p;
		p.x = a;	p.y = b;	p.z = c;
		return p;
	}


	// Calculates 3rd degree polynomial based on array of 4 points
	// and a single variable (u) which is generally between 0 and 1
	Lesson28::POINT_3D Lesson28::Bernstein( float u, POINT_3D* p )
	{
		POINT_3D	a, b, c, d, r;

		a = pointTimes( pow( u, 3 ), p[0] );
		b = pointTimes( 3.0 * pow( u, 2 ) * (1.0 - u), p[1] );
		c = pointTimes( 3.0 * u * pow( (1 - u), 2 ), p[2] );
		d = pointTimes( pow( (1 - u), 3 ), p[3] );

		r = pointAdd( pointAdd( a, b ), pointAdd( c, d ) );

		return r;
	}

	// Generates a display list based on the data in the patch
	// and the number of divisions
	GLuint Lesson28::genBezier( BEZIER_PATCH patch, int divs )
	{
		int			u = 0, v;
		float		py, px, pyold;
		GLuint		drawlist = glGenLists( 1 );		// make the display list
		POINT_3D	temp[4];
		POINT_3D* last = (POINT_3D*)malloc( sizeof( POINT_3D ) * (divs + 1) );
		if ( last == nullptr )
		{
			return 0;
		}
		// array of points to mark the first line of polys

		if ( patch.dlBPatch != NULL )					// get rid of any old display lists
			glDeleteLists( patch.dlBPatch, 1 );

		temp[0] = patch.anchors[0][3];				// the first derived curve (along x axis)
		temp[1] = patch.anchors[1][3];
		temp[2] = patch.anchors[2][3];
		temp[3] = patch.anchors[3][3];

		for ( v = 0; v <= divs; v++ )
		{						// create the first line of points
			px = ((float)v) / ((float)divs);			// percent along y axis
		// use the 4 points from the derives curve to calculate the points along that curve
			last[v] = Bernstein( px, temp );
		}

		glNewList( drawlist, GL_COMPILE );				// Start a new display list
		glBindTexture( GL_TEXTURE_2D, patch.texture );	// Bind the texture

		for ( u = 1; u <= divs; u++ )
		{
			py = ((float)u) / ((float)divs);			// Percent along Y axis
			pyold = ((float)u - 1.0f) / ((float)divs);		// Percent along old Y axis

			temp[0] = Bernstein( py, patch.anchors[0] );	// Calculate new bezier points
			temp[1] = Bernstein( py, patch.anchors[1] );
			temp[2] = Bernstein( py, patch.anchors[2] );
			temp[3] = Bernstein( py, patch.anchors[3] );

			glBegin( GL_TRIANGLE_STRIP );					// Begin a new triangle strip

			for ( v = 0; v <= divs; v++ )
			{
				px = ((float)v) / ((float)divs);			// Percent along the X axis

				glTexCoord2f( pyold, px );				// Apply the old texture coords
#pragma warning ( disable : 6386 6385 )
				glVertex3d( last[v].x, last[v].y, last[v].z );	// Old Point

				last[v] = Bernstein( px, temp );			// Generate new point
#pragma warning ( default : 6386 6385 )
				glTexCoord2f( py, px );					// Apply the new texture coords
				glVertex3d( last[v].x, last[v].y, last[v].z );	// New Point
			}

			glEnd();									// END the triangle srip
		}

		glEndList();								// END the list

		free( last );									// Free the old vertices array
		return drawlist;							// Return the display list
	}

	/************************************************************************************/

	void Lesson28::initBezier( void )
	{
		mybezier.anchors[0][0] = makePoint( -0.75, -0.75, -0.5 );	// set the bezier vertices
		mybezier.anchors[0][1] = makePoint( -0.25, -0.75, 0.0 );
		mybezier.anchors[0][2] = makePoint( 0.25, -0.75, 0.0 );
		mybezier.anchors[0][3] = makePoint( 0.75, -0.75, -0.5 );
		mybezier.anchors[1][0] = makePoint( -0.75, -0.25, -0.75 );
		mybezier.anchors[1][1] = makePoint( -0.25, -0.25, 0.5 );
		mybezier.anchors[1][2] = makePoint( 0.25, -0.25, 0.5 );
		mybezier.anchors[1][3] = makePoint( 0.75, -0.25, -0.75 );
		mybezier.anchors[2][0] = makePoint( -0.75, 0.25, 0.0 );
		mybezier.anchors[2][1] = makePoint( -0.25, 0.25, -0.5 );
		mybezier.anchors[2][2] = makePoint( 0.25, 0.25, -0.5 );
		mybezier.anchors[2][3] = makePoint( 0.75, 0.25, 0.0 );
		mybezier.anchors[3][0] = makePoint( -0.75, 0.75, -0.5 );
		mybezier.anchors[3][1] = makePoint( -0.25, 0.75, -1.0 );
		mybezier.anchors[3][2] = makePoint( 0.25, 0.75, -1.0 );
		mybezier.anchors[3][3] = makePoint( 0.75, 0.75, -0.5 );
		mybezier.dlBPatch = NULL;
	}

	/*****************************************************************************************/
	// Load Bitmaps And Convert To Textures

	BOOL Lesson28::LoadGLTexture( GLuint* texPntr, const char* name )
	{
		BOOL success = FALSE;
		AUX_RGBImageRec* TextureImage = NULL;

		glGenTextures( 1, texPntr );						// Generate 1 texture

		FILE* test = NULL;
		TextureImage = NULL;

		test = fopen( name, "r" );						// test to see if the file exists
		if ( test != NULL )
		{								// if it does
			fclose( test );									// close the file
			TextureImage = auxDIBImageLoad( name );			// and load the texture
		}

		if ( TextureImage != NULL )
		{						// if it loaded
			success = TRUE;

			// Typical Texture Generation Using Data From The Bitmap
			glBindTexture( GL_TEXTURE_2D, *texPntr );
			glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

			if ( TextureImage->data )
				free( TextureImage->data );
		}

		return success;
	}

	/************************************************************************************/
	// (no changes)

	GLvoid Lesson28::ReSizeGLScene( GLsizei width, GLsizei height )		// Resize And Initialize The GL Window
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

	/************************************************************************************/

	int Lesson28::InitGL( GLvoid )										// All Setup For OpenGL Goes Here
	{
		glEnable( GL_TEXTURE_2D );							// Enable Texture Mapping
		glShadeModel( GL_SMOOTH );							// Enable Smooth Shading
		glClearColor( 0.05f, 0.05f, 0.05f, 0.5f );			// Black Background
		glClearDepth( 1.0f );									// Depth Buffer Setup
		glEnable( GL_DEPTH_TEST );							// Enables Depth Testing
		glDepthFunc( GL_LEQUAL );								// The Type Of Depth Testing To Do
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );	// Really Nice Perspective Calculations

		initBezier();											// Initialize the Bezier's control grid
		LoadGLTexture( &(mybezier.texture), "./data/NeHe.bmp" );	// Load the texture
		mybezier.dlBPatch = genBezier( mybezier, divs );			// Generate the patch

		return TRUE;										// Initialization Went OK
	}

	/************************************************************************************/

	int Lesson28::DrawGLScene( GLvoid )
	{								// Here's Where We Do All The Drawing
		int i, j;
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// Clear Screen And Depth Buffer
		glLoadIdentity();									// Reset The Current Modelview Matrix
		glTranslatef( 0.0f, 0.0f, -4.0f );						// Move Left 1.5 Units And Into The Screen 6.0
		glRotatef( -75.0f, 1.0f, 0.0f, 0.0f );
		glRotatef( rotz, 0.0f, 0.0f, 1.0f );						// Rotate The Triangle On The Z axis ( NEW )

		glCallList( mybezier.dlBPatch );						// Call the Bezier's display list
															// this need only be updated when the patch changes

		if ( showCPoints )
		{									// If drawing the grid is toggled on
			glDisable( GL_TEXTURE_2D );
			glColor3f( 1.0f, 0.0f, 0.0f );
			for ( i = 0; i < 4; i++ )
			{								// draw the horizontal lines
				glBegin( GL_LINE_STRIP );
				for ( j = 0; j < 4; j++ )
					glVertex3d( mybezier.anchors[i][j].x, mybezier.anchors[i][j].y, mybezier.anchors[i][j].z );
				glEnd();
			}
			for ( i = 0; i < 4; i++ )
			{								// draw the vertical lines
				glBegin( GL_LINE_STRIP );
				for ( j = 0; j < 4; j++ )
					glVertex3d( mybezier.anchors[j][i].x, mybezier.anchors[j][i].y, mybezier.anchors[j][i].z );
				glEnd();
			}
			glColor3f( 1.0f, 1.0f, 1.0f );
			glEnable( GL_TEXTURE_2D );
		}

		return TRUE;										// Keep Going
	}

	void Lesson28::Update( DWORD milliseconds, bool keys[] )
	{
		if ( keys[VK_LEFT] )	rotz -= 0.8f;		// rotate left
		if ( keys[VK_RIGHT] )	rotz += 0.8f;		// rotate right
		if ( keys[VK_UP] )
		{						// resolution up
			divs++;
			mybezier.dlBPatch = genBezier( mybezier, divs );	// Update the patch
			keys[VK_UP] = FALSE;
		}
		if ( keys[VK_DOWN] && divs > 1 )
		{
			divs--;
			mybezier.dlBPatch = genBezier( mybezier, divs );	// Update the patch
			keys[VK_DOWN] = FALSE;
		}
		if ( keys[VK_SPACE] )
		{					// SPACE toggles showCPoints
			showCPoints = !showCPoints;
			keys[VK_SPACE] = FALSE;
		}
	}

	const char* Lesson28::GetDescription() const
	{
		return "Left/Right - Rotate\n\
				Up/Down - Change Resolution\n\
				Space - Toggle Control Points";
	}
}