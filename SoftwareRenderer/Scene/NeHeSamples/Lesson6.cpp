#include "framework.h"
#include "../gl/glAdapter.h"

GLfloat	xrot;				// X Rotation ( NEW )
GLfloat	yrot;				// Y Rotation ( NEW )
GLfloat	zrot;				// Z Rotation ( NEW )

GLuint	texture[1];			// Storage For One Texture ( NEW )
int LoadGLTextures();

int InitGL( GLvoid )										// All Setup For OpenGL Goes Here
{
	if ( !LoadGLTextures() )								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}

	glEnable( GL_TEXTURE_2D );							// Enable Texture Mapping ( NEW )
	//glShadeModel( GL_SMOOTH );							// Enable Smooth Shading
	//glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );				// Black Background
	//glClearDepth( 1.0f );									// Depth Buffer Setup
	//glEnable( GL_DEPTH_TEST );							// Enables Depth Testing
	//glDepthFunc( GL_LEQUAL );								// The Type Of Depth Testing To Do
	//glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );	// Really Nice Perspective Calculations
	return TRUE;										// Initialization Went OK
}

int DrawGLScene( GLvoid )									// Here's Where We Do All The Drawing
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The View
	glTranslatef( 0.0f, 0.0f, -5.0f );

	glRotatef( xrot, 1.0f, 0.0f, 0.0f );
	glRotatef( yrot, 0.0f, 1.0f, 0.0f );
	glRotatef( zrot, 0.0f, 0.0f, 1.0f );

	glBindTexture( GL_TEXTURE_2D, texture[0] );

	glBegin( GL_QUADS );
	// Front Face
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 1.0f );
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, 1.0f );
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, 1.0f );
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, 1.0f );
	// Back Face
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, -1.0f );
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, -1.0f );
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, -1.0f );
	// Top Face
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, -1.0f );
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, 1.0f, 1.0f );
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, 1.0f, 1.0f );
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, -1.0f );
	// Bottom Face
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f, -1.0f, -1.0f );
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, 1.0f );
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 1.0f );
	// Right face
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, -1.0f );
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, -1.0f );
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, 1.0f );
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, 1.0f );
	// Left Face
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 1.0f );
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, 1.0f );
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, -1.0f );
	glEnd();

	xrot += 0.3f;
	yrot += 0.2f;
	zrot += 0.4f;
	return TRUE;										// Keep Going
}


int LoadGLTextures()									// Load Bitmaps And Convert To Textures
{
	int Status = FALSE;									// Status Indicator

	AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture

	memset( TextureImage, 0, sizeof( void * ) * 1 );           	// Set The Pointer To NULL

	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if ( TextureImage[0] = auxDIBImageLoad( _T("Data/NeHe.bmp") ) )
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