#include "framework.h"
#include "Lesson26.h"

namespace NeHe
{
	Lesson26::Lesson26()
	{
	}

	Lesson26::~Lesson26()
	{
	}

	GLvoid Lesson26::ReSizeGLScene( GLsizei width, GLsizei height )		// Resize And Initialize The GL Window
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

	int Lesson26::LoadGLTextures()                                    // Load Bitmaps And Convert To Textures
	{
		int Status = FALSE;									// Status Indicator
		AUX_RGBImageRec* TextureImage[3];					// Create Storage Space For The Textures
		memset( TextureImage, 0, sizeof( void* ) * 3 );			// Set The Pointer To NULL
		if ( (TextureImage[0] = LoadBMP( "Data/EnvWall.bmp" )) &&// Load The Floor Texture
			(TextureImage[1] = LoadBMP( "Data/Ball.bmp" )) &&	// Load the Light Texture
			(TextureImage[2] = LoadBMP( "Data/EnvRoll.bmp" )) )	// Load the Wall Texture
		{
			Status = TRUE;									// Set The Status To TRUE
			glGenTextures( 3, &texture[0] );					// Create The Texture
			int loop;
			for ( loop = 0; loop < 3; loop++ )				// Loop Through 5 Textures
			{
				glBindTexture( GL_TEXTURE_2D, texture[loop] );
				glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[loop]->sizeX, TextureImage[loop]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[loop]->data );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			}
			for ( loop = 0; loop < 3; loop++ )					// Loop Through 5 Textures
			{
				if ( TextureImage[loop] )						// If Texture Exists
				{
					if ( TextureImage[loop]->data )			// If Texture Image Exists
					{
						free( TextureImage[loop]->data );		// Free The Texture Image Memory
					}
					free( TextureImage[loop] );				// Free The Image Structure 
				}
			}
		}
		return Status;										// Return The Status
	}

	int Lesson26::InitGL( GLvoid )										// All Setup For OpenGL Goes Here
	{
		if ( !LoadGLTextures() )								// If Loading The Textures Failed
		{
			return FALSE;									// Return False
		}
		glShadeModel( GL_SMOOTH );							// Enable Smooth Shading
		glClearColor( 0.2f, 0.5f, 1.0f, 1.0f );				// Background
		glClearDepth( 1.0f );									// Depth Buffer Setup
		glClearStencil( 0 );									// Clear The Stencil Buffer To 0
		glEnable( GL_DEPTH_TEST );							// Enables Depth Testing
		glDepthFunc( GL_LEQUAL );								// The Type Of Depth Testing To Do
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );	// Really Nice Perspective Calculations
		glEnable( GL_TEXTURE_2D );							// Enable 2D Texture Mapping

		glLightfv( GL_LIGHT0, GL_AMBIENT, LightAmb );			// Set The Ambient Lighting For Light0
		glLightfv( GL_LIGHT0, GL_DIFFUSE, LightDif );			// Set The Diffuse Lighting For Light0
		glLightfv( GL_LIGHT0, GL_POSITION, LightPos );		// Set The Position For Light0

		glEnable( GL_LIGHT0 );								// Enable Light 0
		glEnable( GL_LIGHTING );								// Enable Lighting

		q = gluNewQuadric();								// Create A New Quadratic
		gluQuadricNormals( q, GL_SMOOTH );					// Generate Smooth Normals For The Quad
		gluQuadricTexture( q, GL_TRUE );						// Enable Texture Coords For The Quad

		glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );	// Set Up Sphere Mapping
		glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );	// Set Up Sphere Mapping

		return TRUE;										// Initialization Went OK
	}

	void Lesson26::DrawObject()										// Draw Our Ball
	{
		glColor3f( 1.0f, 1.0f, 1.0f );						// Set Color To White
		glBindTexture( GL_TEXTURE_2D, texture[1] );			// Select Texture 2 (1)
		gluSphere( q, 0.35f, 32, 16 );						// Draw First Sphere

		glBindTexture( GL_TEXTURE_2D, texture[2] );			// Select Texture 3 (2)
		glColor4f( 1.0f, 1.0f, 1.0f, 0.4f );					// Set Color To White With 40% Alpha
		glEnable( GL_BLEND );									// Enable Blending
		glBlendFunc( GL_SRC_ALPHA, GL_ONE );					// Set Blending Mode To Mix Based On SRC Alpha
		glEnable( GL_TEXTURE_GEN_S );							// Enable Sphere Mapping
		glEnable( GL_TEXTURE_GEN_T );							// Enable Sphere Mapping

		gluSphere( q, 0.35f, 32, 16 );						// Draw Another Sphere Using New Texture
															// Textures Will Mix Creating A MultiTexture Effect (Reflection)
		glDisable( GL_TEXTURE_GEN_S );						// Disable Sphere Mapping
		glDisable( GL_TEXTURE_GEN_T );						// Disable Sphere Mapping
		glDisable( GL_BLEND );								// Disable Blending
	}

	void Lesson26::DrawFloor()										// Draws The Floor
	{
		glBindTexture( GL_TEXTURE_2D, texture[0] );			// Select Texture 1 (0)
		glBegin( GL_QUADS );									// Begin Drawing A Quad
		glNormal3f( 0.0, 1.0, 0.0 );						// Normal Pointing Up
		glTexCoord2f( 0.0f, 1.0f );					// Bottom Left Of Texture
		glVertex3f( -2.0, 0.0, 2.0 );					// Bottom Left Corner Of Floor

		glTexCoord2f( 0.0f, 0.0f );					// Top Left Of Texture
		glVertex3f( -2.0, 0.0, -2.0 );					// Top Left Corner Of Floor

		glTexCoord2f( 1.0f, 0.0f );					// Top Right Of Texture
		glVertex3f( 2.0, 0.0, -2.0 );					// Top Right Corner Of Floor

		glTexCoord2f( 1.0f, 1.0f );					// Bottom Right Of Texture
		glVertex3f( 2.0, 0.0, 2.0 );					// Bottom Right Corner Of Floor
		glEnd();											// Done Drawing The Quad
	}

	int Lesson26::DrawGLScene( GLvoid )									// Draw Everything
	{
		// Clear Screen, Depth Buffer & Stencil Buffer
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

		// Clip Plane Equations
		double eqr[] = { 0.0f,-1.0f, 0.0f, 0.0f };			// Plane Equation To Use For The Reflected Objects

		glLoadIdentity();									// Reset The Modelview Matrix
		glTranslatef( 0.0f, -0.6f, zoom );					// Zoom And Raise Camera Above The Floor (Up 0.6 Units)
		glColorMask( 0, 0, 0, 0 );								// Set Color Mask
		glEnable( GL_STENCIL_TEST );							// Enable Stencil Buffer For "marking" The Floor
		glStencilFunc( GL_ALWAYS, 1, 1 );						// Always Passes, 1 Bit Plane, 1 As Mask
		glStencilOp( GL_KEEP, GL_KEEP, GL_REPLACE );			// We Set The Stencil Buffer To 1 Where We Draw Any Polygon
															// Keep If Test Fails, Keep If Test Passes But Buffer Test Fails
															// Replace If Test Passes
		glDisable( GL_DEPTH_TEST );							// Disable Depth Testing
		DrawFloor();										// Draw The Floor (Draws To The Stencil Buffer)
															// We Only Want To Mark It In The Stencil Buffer
		glEnable( GL_DEPTH_TEST );							// Enable Depth Testing
		glColorMask( 1, 1, 1, 1 );								// Set Color Mask to TRUE, TRUE, TRUE, TRUE
		glStencilFunc( GL_EQUAL, 1, 1 );						// We Draw Only Where The Stencil Is 1
															// (I.E. Where The Floor Was Drawn)
		glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );				// Don't Change The Stencil Buffer
		glEnable( GL_CLIP_PLANE0 );							// Enable Clip Plane For Removing Artifacts
															// (When The Object Crosses The Floor)
		glClipPlane( GL_CLIP_PLANE0, eqr );					// Equation For Reflected Objects
		glPushMatrix();										// Push The Matrix Onto The Stack
		glScalef( 1.0f, -1.0f, 1.0f );					// Mirror Y Axis
		glLightfv( GL_LIGHT0, GL_POSITION, LightPos );	// Set Up Light0
		glTranslatef( 0.0f, height, 0.0f );				// Position The Object
		glRotatef( xrot, 1.0f, 0.0f, 0.0f );				// Rotate Local Coordinate System On X Axis
		glRotatef( yrot, 0.0f, 1.0f, 0.0f );				// Rotate Local Coordinate System On Y Axis
		DrawObject();									// Draw The Sphere (Reflection)
		glPopMatrix();										// Pop The Matrix Off The Stack
		glDisable( GL_CLIP_PLANE0 );							// Disable Clip Plane For Drawing The Floor
		glDisable( GL_STENCIL_TEST );							// We Don't Need The Stencil Buffer Any More (Disable)
		glLightfv( GL_LIGHT0, GL_POSITION, LightPos );		// Set Up Light0 Position
		glEnable( GL_BLEND );									// Enable Blending (Otherwise The Reflected Object Wont Show)
		glDisable( GL_LIGHTING );								// Since We Use Blending, We Disable Lighting
		glColor4f( 1.0f, 1.0f, 1.0f, 0.8f );					// Set Color To White With 80% Alpha
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );	// Blending Based On Source Alpha And 1 Minus Dest Alpha
		DrawFloor();										// Draw The Floor To The Screen
		glEnable( GL_LIGHTING );								// Enable Lighting
		glDisable( GL_BLEND );								// Disable Blending
		glTranslatef( 0.0f, height, 0.0f );					// Position The Ball At Proper Height
		glRotatef( xrot, 1.0f, 0.0f, 0.0f );					// Rotate On The X Axis
		glRotatef( yrot, 0.0f, 1.0f, 0.0f );					// Rotate On The Y Axis
		DrawObject();										// Draw The Ball
		xrot += xrotspeed;									// Update X Rotation Angle By xrotspeed
		yrot += yrotspeed;									// Update Y Rotation Angle By yrotspeed
		glFlush();											// Flush The GL Pipeline
		return TRUE;										// Everything Went OK
	}

	void Lesson26::Update( DWORD milliseconds, const bool keys[] )							// Process Keyboard Results
	{
		if ( keys[VK_RIGHT] )		yrotspeed += 0.08f;			// Right Arrow Pressed (Increase yrotspeed)
		if ( keys[VK_LEFT] )		yrotspeed -= 0.08f;			// Left Arrow Pressed (Decrease yrotspeed)
		if ( keys[VK_DOWN] )		xrotspeed += 0.08f;			// Down Arrow Pressed (Increase xrotspeed)
		if ( keys[VK_UP] )		xrotspeed -= 0.08f;			// Up Arrow Pressed (Decrease xrotspeed)

		if ( keys['A'] )			zoom += 0.05f;				// 'A' Key Pressed ... Zoom In
		if ( keys['Z'] )			zoom -= 0.05f;				// 'Z' Key Pressed ... Zoom Out

		if ( keys[VK_PRIOR] )		height += 0.03f;				// Page Up Key Pressed Move Ball Up
		if ( keys[VK_NEXT] )		height -= 0.03f;				// Page Down Key Pressed Move Ball Down
	}


	int Lesson26::CleanGL( GLvoid )
	{
		gluDeleteQuadric( q );
		return TRUE;
	}

	const char* Lesson26::GetDescription() const
	{
		return "Arrows - Rotate\n\
				A/Z - Zoom\n\
				PgUp/Dn - Move Up/Down";
	}
}