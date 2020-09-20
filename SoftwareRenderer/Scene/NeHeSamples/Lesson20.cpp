#include "framework.h"
#include "Lesson20.h"
namespace NeHe
{
	Lesson20::Lesson20()
		: mp( false )
		, sp( false )
		, scene( false )
		, loop( 0 )
		, roll( 0.f )
		, texture{ 0, }
	{
	}

	Lesson20::~Lesson20()
	{
	}

	int Lesson20::LoadGLTextures()                                    // Load Bitmaps And Convert To Textures
	{
		int Status = FALSE;                               // Status Indicator
		AUX_RGBImageRec* TextureImage[5];               // Create Storage Space For The Textures
		memset( TextureImage, 0, sizeof( void* ) * 5 );        // Set The Pointer To NULL

		if ( (TextureImage[0] = LoadBMP( "Data/logo.bmp" )) &&	// Logo Texture
			(TextureImage[1] = LoadBMP( "Data/mask1.bmp" )) &&	// First Mask
			(TextureImage[2] = LoadBMP( "Data/image1.bmp" )) &&	// First Image
			(TextureImage[3] = LoadBMP( "Data/mask2.bmp" )) &&	// Second Mask
			(TextureImage[4] = LoadBMP( "Data/image2.bmp" )) )	// Second Image
		{
			Status = TRUE;                            // Set The Status To TRUE
			glGenTextures( 5, &texture[0] );          // Create Five Textures

			for ( loop = 0; loop < 5; loop++ )			// Loop Through All 5 Textures
			{
				glBindTexture( GL_TEXTURE_2D, texture[loop] );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
				glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[loop]->sizeX, TextureImage[loop]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[loop]->data );
			}
		}
		for ( loop = 0; loop < 5; loop++ )						// Loop Through All 5 Textures
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

	GLvoid Lesson20::ReSizeGLScene( GLsizei width, GLsizei height )		// Resize And Initialize The GL Window
	{
		if ( height == 0 )										// Prevent A Divide By Zero By
		{
			height = 1;										// Making Height Equal One
		}

		glViewport( 0, 0, width, height );						// Reset The Current Viewport
		glMatrixMode( GL_PROJECTION );						// Select The Projection Matrix
		glLoadIdentity();									// Reset The Projection Matrix
		gluPerspective( 45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f );	// Calculate Window Aspect Ratio
		glMatrixMode( GL_MODELVIEW );							// Select The Modelview Matrix
		glLoadIdentity();									// Reset The Modelview Matrix
	}

	int Lesson20::InitGL( GLvoid )										// All Setup For OpenGL Goes Here
	{
		if ( !LoadGLTextures() )								// Jump To Texture Loading Routine
		{
			return FALSE;									// If Texture Didn't Load Return FALSE
		}

		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );				// Clear The Background Color To Black
		glClearDepth( 1.0 );									// Enables Clearing Of The Depth Buffer
		glEnable( GL_DEPTH_TEST );							// Enable Depth Testing
		glShadeModel( GL_SMOOTH );							// Enables Smooth Color Shading
		glEnable( GL_TEXTURE_2D );							// Enable 2D Texture Mapping
		return TRUE;										// Initialization Went OK
	}

	int Lesson20::DrawGLScene( GLvoid )									// Here's Where We Do All The Drawing
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// Clear The Screen And The Depth Buffer
		glLoadIdentity();									// Reset The Modelview Matrix
		glTranslatef( 0.0f, 0.0f, -2.0f );						// Move Into The Screen 5 Units

		glBindTexture( GL_TEXTURE_2D, texture[0] );			// Select Our Logo Texture
		glBegin( GL_QUADS );									// Start Drawing A Textured Quad
		glTexCoord2f( 0.0f, -roll + 0.0f ); glVertex3f( -1.1f, -1.1f, 0.0f );	// Bottom Left
		glTexCoord2f( 3.0f, -roll + 0.0f ); glVertex3f( 1.1f, -1.1f, 0.0f );	// Bottom Right
		glTexCoord2f( 3.0f, -roll + 3.0f ); glVertex3f( 1.1f, 1.1f, 0.0f );	// Top Right
		glTexCoord2f( 0.0f, -roll + 3.0f ); glVertex3f( -1.1f, 1.1f, 0.0f );	// Top Left
		glEnd();											// Done Drawing The Quad

		glEnable( GL_BLEND );									// Enable Blending
		glDisable( GL_DEPTH_TEST );							// Disable Depth Testing

		if ( masking )										// Is Masking Enabled?
		{
			glBlendFunc( GL_DST_COLOR, GL_ZERO );				// Blend Screen Color With Zero (Black)
		}

		if ( scene )											// Are We Drawing The Second Scene?
		{
			glTranslatef( 0.0f, 0.0f, -1.0f );					// Translate Into The Screen One Unit
			glRotatef( roll * 360, 0.0f, 0.0f, 1.0f );				// Rotate On The Z Axis 360 Degrees.
			if ( masking )									// Is Masking On?
			{
				glBindTexture( GL_TEXTURE_2D, texture[3] );	// Select The Second Mask Texture
				glBegin( GL_QUADS );							// Start Drawing A Textured Quad
				glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.1f, -1.1f, 0.0f );	// Bottom Left
				glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.1f, -1.1f, 0.0f );	// Bottom Right
				glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.1f, 1.1f, 0.0f );	// Top Right
				glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.1f, 1.1f, 0.0f );	// Top Left
				glEnd();									// Done Drawing The Quad
			}

			glBlendFunc( GL_ONE, GL_ONE );					// Copy Image 2 Color To The Screen
			glBindTexture( GL_TEXTURE_2D, texture[4] );		// Select The Second Image Texture
			glBegin( GL_QUADS );								// Start Drawing A Textured Quad
			glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.1f, -1.1f, 0.0f );	// Bottom Left
			glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.1f, -1.1f, 0.0f );	// Bottom Right
			glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.1f, 1.1f, 0.0f );	// Top Right
			glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.1f, 1.1f, 0.0f );	// Top Left
			glEnd();										// Done Drawing The Quad
		}
		else												// Otherwise
		{
			if ( masking )									// Is Masking On?
			{
				glBindTexture( GL_TEXTURE_2D, texture[1] );	// Select The First Mask Texture
				glBegin( GL_QUADS );							// Start Drawing A Textured Quad
				glTexCoord2f( roll + 0.0f, 0.0f ); glVertex3f( -1.1f, -1.1f, 0.0f );	// Bottom Left
				glTexCoord2f( roll + 4.0f, 0.0f ); glVertex3f( 1.1f, -1.1f, 0.0f );	// Bottom Right
				glTexCoord2f( roll + 4.0f, 4.0f ); glVertex3f( 1.1f, 1.1f, 0.0f );	// Top Right
				glTexCoord2f( roll + 0.0f, 4.0f ); glVertex3f( -1.1f, 1.1f, 0.0f );	// Top Left
				glEnd();									// Done Drawing The Quad
			}

			glBlendFunc( GL_ONE, GL_ONE );					// Copy Image 1 Color To The Screen
			glBindTexture( GL_TEXTURE_2D, texture[2] );		// Select The First Image Texture
			glBegin( GL_QUADS );								// Start Drawing A Textured Quad
			glTexCoord2f( roll + 0.0f, 0.0f ); glVertex3f( -1.1f, -1.1f, 0.0f );	// Bottom Left
			glTexCoord2f( roll + 4.0f, 0.0f ); glVertex3f( 1.1f, -1.1f, 0.0f );	// Bottom Right
			glTexCoord2f( roll + 4.0f, 4.0f ); glVertex3f( 1.1f, 1.1f, 0.0f );	// Top Right
			glTexCoord2f( roll + 0.0f, 4.0f ); glVertex3f( -1.1f, 1.1f, 0.0f );	// Top Left
			glEnd();										// Done Drawing The Quad
		}

		glEnable( GL_DEPTH_TEST );							// Enable Depth Testing
		glDisable( GL_BLEND );								// Disable Blending

		roll += 0.002f;										// Increase Our Texture Roll Variable
		if ( roll > 1.0f )										// Is Roll Greater Than One
		{
			roll -= 1.0f;										// Subtract 1 From Roll
		}

		return TRUE;										// Everything Went OK
	}

	void Lesson20::Update( DWORD milliseconds, const bool keys[] )
	{
		if ( keys[' '] && !sp )				// Is Space Being Pressed?
		{
			sp = TRUE;						// Tell Program Spacebar Is Being Held
			scene = !scene;					// Toggle From One Scene To The Other
		}
		if ( !keys[' '] )						// Has Spacebar Been Released?
		{
			sp = FALSE;						// Tell Program Spacebar Has Been Released
		}

		if ( keys['M'] && !mp )				// Is M Being Pressed?
		{
			mp = TRUE;						// Tell Program M Is Being Held
			masking = !masking;				// Toggle Masking Mode OFF/ON
		}
		if ( !keys['M'] )						// Has M Been Released?
		{
			mp = FALSE;						// Tell Program That M Has Been Released
		}
	}

	const char* Lesson20::GetDescription() const
	{
		return "Space - Change Scene\n\
				M - Toggle Mask";
	}
}