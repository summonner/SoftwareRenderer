#include "framework.h"
#include "Lesson9.h"

namespace NeHe
{
	Lesson9::Lesson9()
		: twinkle( false )
		, tp( false )
		, spin( 0.f )
		, loop( 0 )
		, texture{ 0, }
	{
	}
	
	Lesson9::~Lesson9()
	{
	}

	int Lesson9::LoadGLTextures()                                    // Load Bitmaps And Convert To Textures
	{
		int Status = FALSE;                               // Status Indicator

		AUX_RGBImageRec* TextureImage[1];               // Create Storage Space For The Texture

		memset( TextureImage, 0, sizeof( void* ) * 1 );        // Set The Pointer To NULL

		// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
		if ( TextureImage[0] = LoadBMP( "Data/Star.bmp" ) )
		{
			Status = TRUE;                            // Set The Status To TRUE

			glGenTextures( 1, &texture[0] );          // Create One Texture

			// Create Linear Filtered Texture
			glBindTexture( GL_TEXTURE_2D, texture[0] );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data );
		}
		if ( TextureImage[0] )                            // If Texture Exists
		{
			if ( TextureImage[0]->data )              // If Texture Image Exists
			{
				free( TextureImage[0]->data );    // Free The Texture Image Memory
			}

			free( TextureImage[0] );                  // Free The Image Structure
		}

		return Status;                                  // Return The Status
	}

	GLvoid Lesson9::ReSizeGLScene( GLsizei width, GLsizei height )		// Resize And Initialize The GL Window
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

	int Lesson9::InitGL( GLvoid )										// All Setup For OpenGL Goes Here
	{
		if ( !LoadGLTextures() )								// Jump To Texture Loading Routine
		{
			return FALSE;									// If Texture Didn't Load Return FALSE
		}

		glEnable( GL_TEXTURE_2D );							// Enable Texture Mapping
		glShadeModel( GL_SMOOTH );							// Enable Smooth Shading
		glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );				// Black Background
		glClearDepth( 1.0f );									// Depth Buffer Setup
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );	// Really Nice Perspective Calculations
		glBlendFunc( GL_SRC_ALPHA, GL_ONE );					// Set The Blending Function For Translucency
		glEnable( GL_BLEND );

		for ( loop = 0; loop < num; loop++ )
		{
			star[loop].angle = 0.0f;
			star[loop].dist = (float( loop ) / num) * 5.0f;
			star[loop].r = rand() % 256;
			star[loop].g = rand() % 256;
			star[loop].b = rand() % 256;
		}
		return TRUE;										// Initialization Went OK
	}

	int Lesson9::DrawGLScene( GLvoid )									// Here's Where We Do All The Drawing
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// Clear The Screen And The Depth Buffer
		glBindTexture( GL_TEXTURE_2D, texture[0] );			// Select Our Texture

		for ( loop = 0; loop < num; loop++ )						// Loop Through All The Stars
		{
			glLoadIdentity();								// Reset The View Before We Draw Each Star
			glTranslatef( 0.0f, 0.0f, zoom );					// Zoom Into The Screen (Using The Value In 'zoom')
			glRotatef( tilt, 1.0f, 0.0f, 0.0f );					// Tilt The View (Using The Value In 'tilt')
			glRotatef( star[loop].angle, 0.0f, 1.0f, 0.0f );		// Rotate To The Current Stars Angle
			glTranslatef( star[loop].dist, 0.0f, 0.0f );		// Move Forward On The X Plane
			glRotatef( -star[loop].angle, 0.0f, 1.0f, 0.0f );	// Cancel The Current Stars Angle
			glRotatef( -tilt, 1.0f, 0.0f, 0.0f );				// Cancel The Screen Tilt

			if ( twinkle )
			{
				glColor4ub( star[(num - loop) - 1].r, star[(num - loop) - 1].g, star[(num - loop) - 1].b, 255 );
				glBegin( GL_QUADS );
				glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 0.0f );
				glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, 0.0f );
				glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, 0.0f );
				glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, 0.0f );
				glEnd();
			}

			glRotatef( spin, 0.0f, 0.0f, 1.0f );
			glColor4ub( star[loop].r, star[loop].g, star[loop].b, 255 );
			glBegin( GL_QUADS );
			glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 0.0f );
			glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, 0.0f );
			glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, 0.0f );
			glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, 0.0f );
			glEnd();

			spin += 0.01f;
			star[loop].angle += float( loop ) / num;
			star[loop].dist -= 0.01f;
			if ( star[loop].dist < 0.0f )
			{
				star[loop].dist += 5.0f;
				star[loop].r = rand() % 256;
				star[loop].g = rand() % 256;
				star[loop].b = rand() % 256;
			}
		}
		return TRUE;										// Everything Went OK
	}

	void Lesson9::Update( DWORD milliseconds, bool keys[] )
	{
		if ( keys['T'] && !tp )
		{
			tp = TRUE;
			twinkle = !twinkle;
		}
		if ( !keys['T'] )
		{
			tp = FALSE;
		}

		if ( keys[VK_UP] )
		{
			tilt -= 0.5f;
		}

		if ( keys[VK_DOWN] )
		{
			tilt += 0.5f;
		}

		if ( keys[VK_PRIOR] )
		{
			zoom -= 0.2f;
		}

		if ( keys[VK_NEXT] )
		{
			zoom += 0.2f;
		}
	}


	const char* Lesson9::GetDescription() const
	{
		return "T - Toggle Twinkling\n\
				Up/Down - Tilt\n\
				PgUp/Dn - Zoom";
	}
}