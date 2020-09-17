#include "framework.h"
#include "Lesson10.h"

namespace NeHe
{
	Lesson10::Lesson10()
		: blend( false )
		, fp( false )
		, bp( false )
		, heading( 0.f )
		, xpos( 0.f )
		, zpos( 0.f )
		, yrot( 0.f )
		, filter( 0 )
		, texture{ 0, }
	{
	}

	Lesson10::~Lesson10()
	{
	}

	void Lesson10::readstr( FILE* f, char* string )
	{
		do
		{
			fgets( string, 255, f );
		} while ( (string[0] == '/') || (string[0] == '\n') );
		return;
	}

	void Lesson10::SetupWorld()
	{
		float x, y, z, u, v;
		int numtriangles;
		FILE* filein;
		char oneline[255];
		filein = fopen( "data/world.txt", "rt" );				// File To Load World Data From

		readstr( filein, oneline );
		sscanf( oneline, "NUMPOLLIES %d\n", &numtriangles );

		sector1.triangle = new TRIANGLE[numtriangles];
		sector1.numtriangles = numtriangles;
		for ( int loop = 0; loop < numtriangles; loop++ )
		{
			for ( int vert = 0; vert < 3; vert++ )
			{
				readstr( filein, oneline );
				sscanf( oneline, "%f %f %f %f %f", &x, &y, &z, &u, &v );
				sector1.triangle[loop].vertex[vert].x = x;
				sector1.triangle[loop].vertex[vert].y = y;
				sector1.triangle[loop].vertex[vert].z = z;
				sector1.triangle[loop].vertex[vert].u = u;
				sector1.triangle[loop].vertex[vert].v = v;
			}
		}
		fclose( filein );
		return;
	}

	int Lesson10::LoadGLTextures()                                    // Load Bitmaps And Convert To Textures
	{
		int Status = FALSE;                               // Status Indicator

		AUX_RGBImageRec* TextureImage[1];               // Create Storage Space For The Texture

		memset( TextureImage, 0, sizeof( void* ) * 1 );        // Set The Pointer To NULL

		// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
		if ( TextureImage[0] = LoadBMP( "Data/Mud.bmp" ) )
		{
			Status = TRUE;                            // Set The Status To TRUE

			glGenTextures( 3, &texture[0] );          // Create Three Textures

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

	GLvoid Lesson10::ReSizeGLScene( GLsizei width, GLsizei height )		// Resize And Initialize The GL Window
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

	int Lesson10::InitGL( GLvoid )										// All Setup For OpenGL Goes Here
	{
		if ( !LoadGLTextures() )								// Jump To Texture Loading Routine
		{
			return FALSE;									// If Texture Didn't Load Return FALSE
		}

		glEnable( GL_TEXTURE_2D );							// Enable Texture Mapping
		glBlendFunc( GL_SRC_ALPHA, GL_ONE );					// Set The Blending Function For Translucency
		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );				// This Will Clear The Background Color To Black
		glClearDepth( 1.0 );									// Enables Clearing Of The Depth Buffer
		glDepthFunc( GL_LESS );								// The Type Of Depth Test To Do
		glEnable( GL_DEPTH_TEST );							// Enables Depth Testing
		glShadeModel( GL_SMOOTH );							// Enables Smooth Color Shading
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );	// Really Nice Perspective Calculations

		SetupWorld();

		return TRUE;										// Initialization Went OK
	}

	int Lesson10::DrawGLScene( GLvoid )									// Here's Where We Do All The Drawing
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// Clear The Screen And The Depth Buffer
		glLoadIdentity();									// Reset The View

		GLfloat x_m, y_m, z_m, u_m, v_m;
		GLfloat xtrans = -xpos;
		GLfloat ztrans = -zpos;
		GLfloat ytrans = -walkbias - 0.25f;
		GLfloat sceneroty = 360.0f - yrot;

		int numtriangles;

		glRotatef( lookupdown, 1.0f, 0, 0 );
		glRotatef( sceneroty, 0, 1.0f, 0 );

		glTranslatef( xtrans, ytrans, ztrans );
		glBindTexture( GL_TEXTURE_2D, texture[filter] );

		numtriangles = sector1.numtriangles;

		// Process Each Triangle
		for ( int loop_m = 0; loop_m < numtriangles; loop_m++ )
		{
			glBegin( GL_TRIANGLES );
			glNormal3f( 0.0f, 0.0f, 1.0f );
			x_m = sector1.triangle[loop_m].vertex[0].x;
			y_m = sector1.triangle[loop_m].vertex[0].y;
			z_m = sector1.triangle[loop_m].vertex[0].z;
			u_m = sector1.triangle[loop_m].vertex[0].u;
			v_m = sector1.triangle[loop_m].vertex[0].v;
			glTexCoord2f( u_m, v_m ); glVertex3f( x_m, y_m, z_m );

			x_m = sector1.triangle[loop_m].vertex[1].x;
			y_m = sector1.triangle[loop_m].vertex[1].y;
			z_m = sector1.triangle[loop_m].vertex[1].z;
			u_m = sector1.triangle[loop_m].vertex[1].u;
			v_m = sector1.triangle[loop_m].vertex[1].v;
			glTexCoord2f( u_m, v_m ); glVertex3f( x_m, y_m, z_m );

			x_m = sector1.triangle[loop_m].vertex[2].x;
			y_m = sector1.triangle[loop_m].vertex[2].y;
			z_m = sector1.triangle[loop_m].vertex[2].z;
			u_m = sector1.triangle[loop_m].vertex[2].u;
			v_m = sector1.triangle[loop_m].vertex[2].v;
			glTexCoord2f( u_m, v_m ); glVertex3f( x_m, y_m, z_m );
			glEnd();
		}
		return TRUE;										// Everything Went OK
	}


	void Lesson10::Update( DWORD milliseconds, const bool keys[] )
	{
		if ( keys['B'] && !bp )
		{
			bp = TRUE;
			blend = !blend;
			if ( !blend )
			{
				glDisable( GL_BLEND );
				glEnable( GL_DEPTH_TEST );
			}
			else
			{
				glEnable( GL_BLEND );
				glDisable( GL_DEPTH_TEST );
			}
		}
		if ( !keys['B'] )
		{
			bp = FALSE;
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

			xpos -= (float)sin( heading * piover180 ) * 0.05f;
			zpos -= (float)cos( heading * piover180 ) * 0.05f;
			if ( walkbiasangle >= 359.0f )
			{
				walkbiasangle = 0.0f;
			}
			else
			{
				walkbiasangle += 10;
			}
			walkbias = (float)sin( walkbiasangle * piover180 ) / 20.0f;
		}

		if ( keys[VK_DOWN] )
		{
			xpos += (float)sin( heading * piover180 ) * 0.05f;
			zpos += (float)cos( heading * piover180 ) * 0.05f;
			if ( walkbiasangle <= 1.0f )
			{
				walkbiasangle = 359.0f;
			}
			else
			{
				walkbiasangle -= 10;
			}
			walkbias = (float)sin( walkbiasangle * piover180 ) / 20.0f;
		}

		if ( keys[VK_RIGHT] )
		{
			heading -= 1.0f;
			yrot = heading;
		}

		if ( keys[VK_LEFT] )
		{
			heading += 1.0f;
			yrot = heading;
		}

		if ( keys[VK_PRIOR] )
		{
			lookupdown -= 1.0f;
		}

		if ( keys[VK_NEXT] )
		{
			lookupdown += 1.0f;
		}
	}

	const char* Lesson10::GetDescription() const
	{
		return "F - Change Texture Filter\n\
				B - Toggle Blending\n\
				PgUp/Dn - Look up/down\n\
				Arrow - Move";
	}
}