#include "framework.h"
#include "Lesson23.h"

namespace NeHe
{
	Lesson23::Lesson23()
		: xrot( 0.f )
		, yrot( 0.f )
		, xspeed( 0.f )
		, yspeed( 0.f )
		, filter( 0 )
		, texture{ 0, }
		, part1( 0 )
		, part2( 0 )
		, quadratic( nullptr )
		, object( 0 )
		, light( false )
		, lp( false )
		, fp( false )
		, sp( false )
	{
	}

	Lesson23::~Lesson23()
	{
	}

	int Lesson23::LoadGLTextures()									// Load Bitmaps And Convert To Textures
	{
		int Status = FALSE;									// Status Indicator

		AUX_RGBImageRec* TextureImage[2];					// Create Storage Space For The Texture

		memset( TextureImage, 0, sizeof( void* ) * 2 );           	// Set The Pointer To NULL

		// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
		if ( (TextureImage[0] = LoadBMP( "Data/BG.bmp" )) &&
			(TextureImage[1] = LoadBMP( "Data/Reflect.bmp" )) )
		{
			Status = TRUE;									// Set The Status To TRUE

			glGenTextures( 6, &texture[0] );					// Create Three Textures (For Two Images)

			int loop;
			for ( loop = 0; loop < 2; loop++ )
			{
				// Create Nearest Filtered Texture
				glBindTexture( GL_TEXTURE_2D, texture[loop] );	// Gen Tex 0 and 1
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
				glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[loop]->sizeX, TextureImage[loop]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[loop]->data );

				// Create Linear Filtered Texture
				glBindTexture( GL_TEXTURE_2D, texture[loop + 2] );	// Gen Tex 2 and 3 4
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
				glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[loop]->sizeX, TextureImage[loop]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[loop]->data );

				// Create MipMapped Texture
				glBindTexture( GL_TEXTURE_2D, texture[loop + 4] );	// Gen Tex 4 and 5
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
				gluBuild2DMipmaps( GL_TEXTURE_2D, 3, TextureImage[loop]->sizeX, TextureImage[loop]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[loop]->data );
			}
			for ( loop = 0; loop < 2; loop++ )
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
		}

		return Status;										// Return The Status
	}

	GLvoid Lesson23::ReSizeGLScene( GLsizei width, GLsizei height )		// Resize And Initialize The GL Window
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

	int Lesson23::InitGL( GLvoid )										// All Setup For OpenGL Goes Here
	{
		if ( !LoadGLTextures() )								// Jump To Texture Loading Routine
		{
			return FALSE;									// If Texture Didn't Load Return FALSE
		}

		glEnable( GL_TEXTURE_2D );							// Enable Texture Mapping
		glShadeModel( GL_SMOOTH );							// Enable Smooth Shading
		glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );				// Black Background
		glClearDepth( 1.0f );									// Depth Buffer Setup
		glEnable( GL_DEPTH_TEST );							// Enables Depth Testing
		glDepthFunc( GL_LEQUAL );								// The Type Of Depth Testing To Do
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );	// Really Nice Perspective Calculations

		glLightfv( GL_LIGHT1, GL_AMBIENT, LightAmbient );		// Setup The Ambient Light
		glLightfv( GL_LIGHT1, GL_DIFFUSE, LightDiffuse );		// Setup The Diffuse Light
		glLightfv( GL_LIGHT1, GL_POSITION, LightPosition );	// Position The Light
		glEnable( GL_LIGHT1 );								// Enable Light One

		quadratic = gluNewQuadric();							// Create A Pointer To The Quadric Object (Return 0 If No Memory)
		gluQuadricNormals( quadratic, GLU_SMOOTH );			// Create Smooth Normals 
		gluQuadricTexture( quadratic, GL_TRUE );				// Create Texture Coords 

		glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP ); // Set The Texture Generation Mode For S To Sphere Mapping (NEW)
		glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP ); // Set The Texture Generation Mode For T To Sphere Mapping (NEW)

		return TRUE;										// Initialization Went OK
	}

	GLvoid Lesson23::glDrawCube()
	{
		glBegin( GL_QUADS );
		// Front Face
		glNormal3f( 0.0f, 0.0f, 0.5f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 1.0f );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, 1.0f );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, 1.0f );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, 1.0f );
		// Back Face
		glNormal3f( 0.0f, 0.0f, -0.5f );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, -1.0f );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, -1.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, -1.0f );
		// Top Face
		glNormal3f( 0.0f, 0.5f, 0.0f );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, -1.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, 1.0f, 1.0f );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, 1.0f, 1.0f );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, -1.0f );
		// Bottom Face
		glNormal3f( 0.0f, -0.5f, 0.0f );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f, -1.0f, -1.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, 1.0f );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 1.0f );
		// Right Face
		glNormal3f( 0.5f, 0.0f, 0.0f );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, -1.0f );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, -1.0f );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, 1.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, 1.0f );
		// Left Face
		glNormal3f( -0.5f, 0.0f, 0.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 1.0f );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, 1.0f );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, -1.0f );
		glEnd();
	}

	int Lesson23::DrawGLScene( GLvoid )									// Here's Where We Do All The Drawing
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// Clear The Screen And The Depth Buffer
		glLoadIdentity();									// Reset The View

		glTranslatef( 0.0f, 0.0f, z );

		glEnable( GL_TEXTURE_GEN_S );							// Enable Texture Coord Generation For S (NEW)
		glEnable( GL_TEXTURE_GEN_T );							// Enable Texture Coord Generation For T (NEW)

		glBindTexture( GL_TEXTURE_2D, texture[filter + (filter + 1)] ); // This Will Select The Sphere Map
		glPushMatrix();
		glRotatef( xrot, 1.0f, 0.0f, 0.0f );
		glRotatef( yrot, 0.0f, 1.0f, 0.0f );
		switch ( object )
		{
		case 0:
			glDrawCube();
			break;
		case 1:
			glTranslatef( 0.0f, 0.0f, -1.5f );					// Center The Cylinder
			gluCylinder( quadratic, 1.0f, 1.0f, 3.0f, 32, 32 );	// A Cylinder With A Radius Of 0.5 And A Height Of 2
			break;
		case 2:
			gluSphere( quadratic, 1.3f, 32, 32 );				// Draw A Sphere With A Radius Of 1 And 16 Longitude And 16 Latitude Segments
			break;
		case 3:
			glTranslatef( 0.0f, 0.0f, -1.5f );					// Center The Cone
			gluCylinder( quadratic, 1.0f, 0.0f, 3.0f, 32, 32 );	// A Cone With A Bottom Radius Of .5 And A Height Of 2
			break;
		};

		glPopMatrix();
		glDisable( GL_TEXTURE_GEN_S );
		glDisable( GL_TEXTURE_GEN_T );

		glBindTexture( GL_TEXTURE_2D, texture[filter * 2] );	// This Will Select The BG Maps...
		glPushMatrix();
		glTranslatef( 0.0f, 0.0f, -24.0f );
		glBegin( GL_QUADS );
		glNormal3f( 0.0f, 0.0f, 1.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -13.3f, -10.0f, 10.0f );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 13.3f, -10.0f, 10.0f );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 13.3f, 10.0f, 10.0f );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -13.3f, 10.0f, 10.0f );
		glEnd();
		glPopMatrix();

		xrot += xspeed;
		yrot += yspeed;
		return TRUE;										// Keep Going
	}

	void Lesson23::Update( DWORD milliseconds, const bool keys[] )
	{
		if ( keys['L'] && !lp )
		{
			lp = TRUE;
			light = !light;
			if ( !light )
			{
				glDisable( GL_LIGHTING );
			}
			else
			{
				glEnable( GL_LIGHTING );
			}
		}
		if ( !keys['L'] )
		{
			lp = FALSE;
		}
		if ( keys['F'] && !fp )
		{
			fp = TRUE;
			filter += 1;
			if ( filter > 2 )
			{
				filter = 0;
			}
		}
		if ( !keys['F'] )
		{
			fp = FALSE;
		}
		if ( keys[' '] && !sp )
		{
			sp = TRUE;
			object++;
			if ( object > 3 )
				object = 0;
		}
		if ( !keys[' '] )
		{
			sp = FALSE;
		}
		if ( keys[VK_PRIOR] )
		{
			z -= 0.02f;
		}
		if ( keys[VK_NEXT] )
		{
			z += 0.02f;
		}
		if ( keys[VK_UP] )
		{
			xspeed -= 0.01f;
		}
		if ( keys[VK_DOWN] )
		{
			xspeed += 0.01f;
		}
		if ( keys[VK_RIGHT] )
		{
			yspeed += 0.01f;
		}
		if ( keys[VK_LEFT] )
		{
			yspeed -= 0.01f;
		}
	}

	int Lesson23::CleanGL( GLvoid )
	{
		gluDeleteQuadric( quadratic );
		return TRUE;
	}
}