#include "framework.h"
#include "Lesson12.h"

namespace NeHe
{
	static GLfloat boxcol[5][3] =
	{
		{1.0f,0.0f,0.0f},{1.0f,0.5f,0.0f},{1.0f,1.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,1.0f,1.0f}
	};

	static GLfloat topcol[5][3] =
	{
		{.5f,0.0f,0.0f},{0.5f,0.25f,0.0f},{0.5f,0.5f,0.0f},{0.0f,0.5f,0.0f},{0.0f,0.5f,0.5f}
	};

	Lesson12::Lesson12()
		: box( 0 )
		, top( 0 )
		, xloop( 0 )
		, yloop( 0 )
		, xrot( 0.f )
		, yrot( 0.f )
		, texture{ 0, }
	{
	}

	Lesson12::~Lesson12()
	{
	}

	// Build Cube Display Lists
	GLvoid Lesson12::BuildLists()
	{
		box = glGenLists( 2 );									// Generate 2 Different Lists
		glNewList( box, GL_COMPILE );							// Start With The Box List
		glBegin( GL_QUADS );
		// Bottom Face
		glNormal3f( 0.0f, -1.0f, 0.0f );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f, -1.0f, -1.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, 1.0f );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 1.0f );
		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 1.0f );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, 1.0f );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, 1.0f );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, 1.0f );
		// Back Face
		glNormal3f( 0.0f, 0.0f, -1.0f );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, -1.0f );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, -1.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, -1.0f );
		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, -1.0f );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, -1.0f );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, 1.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, 1.0f );
		// Left Face
		glNormal3f( -1.0f, 0.0f, 0.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 1.0f );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, 1.0f );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, -1.0f );
		glEnd();
		glEndList();
		top = box + 1;											// Storage For "Top" Is "Box" Plus One
		glNewList( top, GL_COMPILE );							// Now The "Top" Display List
		glBegin( GL_QUADS );
		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, -1.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, 1.0f, 1.0f );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, 1.0f, 1.0f );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, -1.0f );
		glEnd();
		glEndList();
	}

	int Lesson12::LoadGLTextures()									// Load Bitmaps And Convert To Textures
	{
		int Status = FALSE;									// Status Indicator

		AUX_RGBImageRec* TextureImage[1];					// Create Storage Space For The Texture

		memset( TextureImage, 0, sizeof( void* ) * 1 );           	// Set The Pointer To NULL

		// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
		if ( TextureImage[0] = LoadBMP( "Data/Cube.bmp" ) )
		{
			Status = TRUE;									// Set The Status To TRUE

			glGenTextures( 1, &texture[0] );					// Create The Texture

			// Typical Texture Generation Using Data From The Bitmap
			glBindTexture( GL_TEXTURE_2D, texture[0] );
			glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		}

		if ( TextureImage[0] )									// If Texture Exists
		{
			if ( TextureImage[0]->data )							// If Texture Image Exists
			{
				free( TextureImage[0]->data );					// Free The Texture Image Memory
			}

			free( TextureImage[0] );								// Free The Image Structure
		}

		return Status;										// Return The Status
	}

	GLvoid Lesson12::ReSizeGLScene( GLsizei width, GLsizei height )		// Resize And Initialize The GL Window
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

	int Lesson12::InitGL( GLvoid )										// All Setup For OpenGL Goes Here
	{
		if ( !LoadGLTextures() )								// Jump To Texture Loading Routine
		{
			return FALSE;									// If Texture Didn't Load Return FALSE
		}
		BuildLists();										// Jump To The Code That Creates Our Display Lists

		glEnable( GL_TEXTURE_2D );							// Enable Texture Mapping
		glShadeModel( GL_SMOOTH );							// Enable Smooth Shading
		glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );				// Black Background
		glClearDepth( 1.0f );									// Depth Buffer Setup
		glEnable( GL_DEPTH_TEST );							// Enables Depth Testing
		glDepthFunc( GL_LEQUAL );								// The Type Of Depth Testing To Do
		glEnable( GL_LIGHT0 );								// Quick And Dirty Lighting (Assumes Light0 Is Set Up)
		glEnable( GL_LIGHTING );								// Enable Lighting
		glEnable( GL_COLOR_MATERIAL );						// Enable Material Coloring
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );	// Really Nice Perspective Calculations
		return TRUE;										// Initialization Went OK
	}

	int Lesson12::DrawGLScene( GLvoid )									// Here's Where We Do All The Drawing
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// Clear The Screen And The Depth Buffer

		glBindTexture( GL_TEXTURE_2D, texture[0] );
		for ( yloop = 1; yloop < 6; yloop++ )
		{
			for ( xloop = 0; xloop < yloop; xloop++ )
			{
				glLoadIdentity();							// Reset The View
				glTranslatef( 1.4f + (float( xloop ) * 2.8f) - (float( yloop ) * 1.4f), ((6.0f - float( yloop )) * 2.4f) - 7.0f, -20.0f );
				glRotatef( 45.0f - (2.0f * yloop) + xrot, 1.0f, 0.0f, 0.0f );
				glRotatef( 45.0f + yrot, 0.0f, 1.0f, 0.0f );
				glColor3fv( boxcol[yloop - 1] );
				glCallList( box );
				glColor3fv( topcol[yloop - 1] );
				glCallList( top );
			}
		}
		return TRUE;										// Keep Going
	}

	int Lesson12::CleanGL( GLvoid )								// Properly Kill The Window
	{
		glDeleteLists( box, 2 );
		return TRUE;
	}

	void Lesson12::Update( DWORD milliseconds, bool keys[] )
	{
		if ( keys[VK_LEFT] )
		{
			yrot -= 0.2f;
		}
		if ( keys[VK_RIGHT] )
		{
			yrot += 0.2f;
		}
		if ( keys[VK_UP] )
		{
			xrot -= 0.2f;
		}
		if ( keys[VK_DOWN] )
		{
			xrot += 0.2f;
		}
	}

	const char* Lesson12::GetDescription() const
	{
		return "Arrows - Rotate";
	}
}