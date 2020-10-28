#include "framework.h"
#include "Lesson8.h"

namespace NeHe
{
	Lesson8::Lesson8()
		: light( false )
		, blend( false )
		, lp( false )
		, fp( false )
		, bp( false )
		, xrot( 0.f )
		, yrot( 0.f )
		, xspeed( 0.f )
		, yspeed( 0.f )
		, filter( 0 )
		, texture{ 0, }
	{
	}

	Lesson8::~Lesson8()
	{
	}
	
	int Lesson8::LoadGLTextures()									// Load Bitmaps And Convert To Textures
	{
		int Status = FALSE;									// Status Indicator

		AUX_RGBImageRec* TextureImage[1];					// Create Storage Space For The Texture

		memset( TextureImage, 0, sizeof( void* ) * 1 );           	// Set The Pointer To NULL

		// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
		if ( TextureImage[0] = LoadBMP( "Data/glass.bmp" ) )
		{
			Status = TRUE;									// Set The Status To TRUE

			glGenTextures( 3, &texture[0] );					// Create Three Textures

			// Create Nearest Filtered Texture
			glBindTexture( GL_TEXTURE_2D, texture[0] );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
			glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data );

			// Create Linear Filtered Texture
			glBindTexture( GL_TEXTURE_2D, texture[1] );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data );

			// Create MipMapped Texture
			glBindTexture( GL_TEXTURE_2D, texture[2] );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
			gluBuild2DMipmaps( GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data );
		}

		if ( TextureImage[0] )								// If Texture Exists
		{
			if ( TextureImage[0]->data )						// If Texture Image Exists
			{
				free( TextureImage[0]->data );				// Free The Texture Image Memory
			}

			free( TextureImage[0] );							// Free The Image Structure
		}

		return Status;										// Return The Status
	}

	GLvoid Lesson8::ReSizeGLScene( GLsizei width, GLsizei height )		// Resize And Initialize The GL Window
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

	int Lesson8::InitGL( GLvoid )										// All Setup For OpenGL Goes Here
	{
		if ( !LoadGLTextures() )								// Jump To Texture Loading Routine
		{
			return FALSE;									// If Texture Didn't Load Return FALSE
		}

		glEnable( GL_TEXTURE_2D );							// Enable Texture Mapping
		//glShadeModel( GL_SMOOTH );							// Enable Smooth Shading
		glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );				// Black Background
		glClearDepth( 1.0f );									// Depth Buffer Setup
		glEnable( GL_DEPTH_TEST );							// Enables Depth Testing
		glDepthFunc( GL_LEQUAL );								// The Type Of Depth Testing To Do
		//glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );	// Really Nice Perspective Calculations

		glLightfv( GL_LIGHT1, GL_AMBIENT, LightAmbient );		// Setup The Ambient Light
		glLightfv( GL_LIGHT1, GL_DIFFUSE, LightDiffuse );		// Setup The Diffuse Light
		glLightfv( GL_LIGHT1, GL_POSITION, LightPosition );	// Position The Light
		glEnable( GL_LIGHT1 );								// Enable Light One

		glColor4f( 1.0f, 1.0f, 1.0f, 0.5 );					// Full Brightness.  50% Alpha
		glBlendFunc( GL_SRC_ALPHA, GL_ONE );					// Set The Blending Function For Translucency

		return TRUE;										// Initialization Went OK
	}

	int Lesson8::DrawGLScene( GLvoid )									// Here's Where We Do All The Drawing
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// Clear The Screen And The Depth Buffer
		glLoadIdentity();									// Reset The View
		glTranslatef( 0.0f, 0.0f, z );

		glRotatef( xrot, 1.0f, 0.0f, 0.0f );
		glRotatef( yrot, 0.0f, 1.0f, 0.0f );

		glBindTexture( GL_TEXTURE_2D, texture[filter] );

		glBegin( GL_QUADS );
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
		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, -1.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, 1.0f, 1.0f );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, 1.0f, 1.0f );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, -1.0f );
		// Bottom Face
		glNormal3f( 0.0f, -1.0f, 0.0f );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f, -1.0f, -1.0f );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, 1.0f );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 1.0f );
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

		xrot += xspeed;
		yrot += yspeed;
		return TRUE;										// Keep Going
	}

	void Lesson8::Update( DWORD milliseconds, bool keys[] )
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
		// Blending Code Starts Here
		if ( keys['B'] && !bp )
		{
			bp = TRUE;
			blend = !blend;
			if ( blend )
			{
				glEnable( GL_BLEND );			// Turn Blending On
				glDisable( GL_DEPTH_TEST );	// Turn Depth Testing Off
			}
			else
			{
				glDisable( GL_BLEND );		// Turn Blending Off
				glEnable( GL_DEPTH_TEST );	// Turn Depth Testing On
			}
		}
		if ( !keys['B'] )
		{
			bp = FALSE;
		}
		// Blending Code Ends Here
	}

	const char* Lesson8::GetDescription() const
	{
		return "L - Toggle light\n\
				F - Change Texture Filter\n\
				B - Toggle Blending\n\
				PgUp/Dn - Zoom\n\
				Arrows - Rotate";
	}
}