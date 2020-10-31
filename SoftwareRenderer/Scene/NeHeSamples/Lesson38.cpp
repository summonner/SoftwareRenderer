#include "framework.h"
#include "Lesson38.h"
#include <resource.h>

namespace NeHe
{
	Lesson38::Lesson38()
	{
	}

	Lesson38::~Lesson38()
	{
	}

	void Lesson38::SetObject( int loop )										// Sets The Initial Value Of Each Object (Random)
	{
		obj[loop].tex = rand() % 3;										// Texture Can Be One Of 3 Textures
		obj[loop].x = rand() % 34 - 17.0f;								// Random x Value From -17.0f To 17.0f
		obj[loop].y = 18.0f;											// Set y Position To 18 (Off Top Of Screen)
		obj[loop].z = -((rand() % 30000 / 1000.0f) + 10.0f);				// z Is A Random Value From -10.0f To -40.0f
		obj[loop].spinzi = (rand() % 10000) / 5000.0f - 1.0f;				// spinzi Is A Random Value From -1.0f To 1.0f
		obj[loop].flap = 0.0f;										// flap Starts Off At 0.0f;
		obj[loop].fi = 0.05f + (rand() % 100) / 1000.0f;					// fi Is A Random Value From 0.05f To 0.15f
		obj[loop].yi = 0.001f + (rand() % 1000) / 10000.0f;					// yi Is A Random Value From 0.001f To 0.101f
	}

	void Lesson38::LoadGLTextures()											// Creates Textures From Bitmaps In The Resource File
	{
		HBITMAP hBMP;												// Handle Of The Bitmap
		BITMAP	BMP;												// Bitmap Structure

		// The ID Of The 3 Bitmap Images We Want To Load From The Resource File
		byte	Texture[] = { IDB_BUTTERFLY1,	IDB_BUTTERFLY2,	IDB_BUTTERFLY3 };

		glGenTextures( sizeof( Texture ), &texture[0] );				// Generate 3 Textures (sizeof(Texture)=3 ID's)
		for ( int loop = 0; loop < sizeof( Texture ); loop++ )				// Loop Through All The ID's (Bitmap Images)
		{
			hBMP = (HBITMAP)LoadImage( GetModuleHandle( NULL ), MAKEINTRESOURCE( Texture[loop] ), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
			if ( hBMP )												// Does The Bitmap Exist?
			{														// If So...
				GetObject( hBMP, sizeof( BMP ), &BMP );					// Get The Object
																	// hBMP: Handle To Graphics Object
																	// sizeof(BMP): Size Of Buffer For Object Information
																	// Buffer For Object Information
				glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );				// Pixel Storage Mode (Word Alignment / 4 Bytes)
				glBindTexture( GL_TEXTURE_2D, texture[loop] );		// Bind Our Texture
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );	// Linear Filtering
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR ); // Mipmap Linear Filtering

				// Generate Mipmapped Texture (3 Bytes, Width, Height And Data From The BMP)
				gluBuild2DMipmaps( GL_TEXTURE_2D, 3, BMP.bmWidth, BMP.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits );
				DeleteObject( hBMP );									// Delete The Bitmap Object
			}
		}
	}

	int Lesson38::InitGL( GLvoid )					// Any GL Init Code & User Initialiazation Goes Here
	{
		// Start Of User Initialization
		LoadGLTextures();											// Load The Textures From Our Resource File

		glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );						// Black Background
		glClearDepth( 1.0f );										// Depth Buffer Setup
		glDepthFunc( GL_LEQUAL );									// The Type Of Depth Testing (Less Or Equal)
		glDisable( GL_DEPTH_TEST );									// Disable Depth Testing
		glShadeModel( GL_SMOOTH );									// Select Smooth Shading
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );			// Set Perspective Calculations To Most Accurate
		glEnable( GL_TEXTURE_2D );									// Enable Texture Mapping
		glBlendFunc( GL_ONE, GL_SRC_ALPHA );							// Set Blending Mode (Cheap / Quick)
		glEnable( GL_BLEND );											// Enable Blending

		for ( int loop = 0; loop < 50; loop++ )							// Loop To Initialize 50 Objects
		{
			SetObject( loop );										// Call SetObject To Assign New Random Values
		}

		return TRUE;												// Return TRUE (Initialization Successful)
	}

	int Lesson38::CleanGL( GLvoid )										// Any User DeInitialization Goes Here
	{
		return TRUE;
	}

	void Lesson38::Update( DWORD milliseconds, bool keys[] )								// Perform Motion Updates Here
	{
	}

	int Lesson38::DrawGLScene( GLvoid )												// Draw The Scene
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );		// Clear Screen And Depth Buffer

		for ( int loop = 0; loop < 50; loop++ )							// Loop Of 50 (Draw 50 Objects)
		{
			glLoadIdentity();										// Reset The Modelview Matrix
			glBindTexture( GL_TEXTURE_2D, texture[obj[loop].tex] );	// Bind Our Texture
			glTranslatef( obj[loop].x, obj[loop].y, obj[loop].z );		// Position The Object
			glRotatef( 45.0f, 1.0f, 0.0f, 0.0f );						// Rotate On The X-Axis
			glRotatef( (obj[loop].spinz), 0.0f, 0.0f, 1.0f );			// Spin On The Z-Axis

			glBegin( GL_TRIANGLES );									// Begin Drawing Triangles
				// First Triangle														    _____
			glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, 0.0f );				//	(2)|    / (1)
			glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, obj[loop].flap );	//	   |  /
			glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 0.0f );				//	(3)|/

			// Second Triangle
			glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, 0.0f );				//	       /|(1)
			glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 0.0f );				//	     /  |
			glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, obj[loop].flap );	//	(2)/____|(3)

			glEnd();												// Done Drawing Triangles

			obj[loop].y -= obj[loop].yi;								// Move Object Down The Screen
			obj[loop].spinz += obj[loop].spinzi;						// Increase Z Rotation By spinzi
			obj[loop].flap += obj[loop].fi;							// Increase flap Value By fi

			if ( obj[loop].y < -18.0f )									// Is Object Off The Screen?
			{
				SetObject( loop );									// If So, Reassign New Values
			}

			if ( (obj[loop].flap > 1.0f) || (obj[loop].flap < -1.0f) )	// Time To Change Flap Direction?
			{
				obj[loop].fi = -obj[loop].fi;							// Change Direction By Making fi = -fi
			}
		}

		Sleep( 15 );													// Create A Short Delay (15 Milliseconds)

		glFlush();													// Flush The GL Rendering Pipeline
		return TRUE;
	}
}