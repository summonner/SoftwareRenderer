#include "framework.h"
#include "Lesson21.h"
#pragma comment ( lib, "winmm.lib" )

namespace NeHe
{
	Lesson21::Lesson21()
		: vline{ 0, }
		, hline{ 0, }
		, ap( false )
		, filled( false )
		, gameover( false )
		, loop1( 0 )
		, loop2( 0 )
		, delay( 0 )
		, texture{ 0, }
		, base( 0 )
	{
		ResetObjects();												// Set Player / Enemy Starting Positions
		TimerInit();
	}

	Lesson21::~Lesson21()
	{
	}

	void Lesson21::TimerInit( void )										// Initialize Our Timer (Get It Ready)
	{
		memset( &timer, 0, sizeof( timer ) );						// Clear Our Timer Structure

		// Check To See If A Performance Counter Is Available
		// If One Is Available The Timer Frequency Will Be Updated
		if ( !QueryPerformanceFrequency( (LARGE_INTEGER*)&timer.frequency ) )
		{
			// No Performace Counter Available
			timer.performance_timer = FALSE;					// Set Performance Timer To FALSE
			timer.mm_timer_start = timeGetTime();			// Use timeGetTime() To Get Current Time
			timer.resolution = 1.0f / 1000.0f;				// Set Our Timer Resolution To .001f
			timer.frequency = 1000;						// Set Our Timer Frequency To 1000
			timer.mm_timer_elapsed = timer.mm_timer_start;		// Set The Elapsed Time To The Current Time
		}
		else
		{
			// Performance Counter Is Available, Use It Instead Of The Multimedia Timer
			// Get The Current Time And Store It In performance_timer_start
			QueryPerformanceCounter( (LARGE_INTEGER*)&timer.performance_timer_start );
			timer.performance_timer = TRUE;				// Set Performance Timer To TRUE
			// Calculate The Timer Resolution Using The Timer Frequency
			timer.resolution = (float)(((double)1.0f) / ((double)timer.frequency));
			// Set The Elapsed Time To The Current Time
			timer.performance_timer_elapsed = timer.performance_timer_start;
		}
	}

	float Lesson21::TimerGetTime()										// Get Time In Milliseconds
	{
		__int64 time;											// time Will Hold A 64 Bit Integer

		if ( timer.performance_timer )							// Are We Using The Performance Timer?
		{
			QueryPerformanceCounter( (LARGE_INTEGER*)&time );	// Grab The Current Performance Time
			// Return The Current Time Minus The Start Time Multiplied By The Resolution And 1000 (To Get MS)
			return ((float)(time - timer.performance_timer_start) * timer.resolution) * 1000.0f;
		}
		else
		{
			// Return The Current Time Minus The Start Time Multiplied By The Resolution And 1000 (To Get MS)
			return((float)(timeGetTime() - timer.mm_timer_start) * timer.resolution) * 1000.0f;
		}
	}

	void Lesson21::ResetObjects( void )										// Reset Player And Enemies
	{
		player.x = 0;												// Reset Player X Position To Far Left Of The Screen
		player.y = 0;												// Reset Player Y Position To The Top Of The Screen
		player.fx = 0;											// Set Fine X Position To Match
		player.fy = 0;											// Set Fine Y Position To Match

		for ( loop1 = 0; loop1 < (stage * level); loop1++ )				// Loop Through All The Enemies
		{
			enemy[loop1].x = 5 + rand() % 6;							// Select A Random X Position
			enemy[loop1].y = rand() % 11;							// Select A Random Y Position
			enemy[loop1].fx = enemy[loop1].x * 60;					// Set Fine X To Match
			enemy[loop1].fy = enemy[loop1].y * 40;					// Set Fine Y To Match
		}
	}

	int Lesson21::LoadGLTextures()										// Load Bitmaps And Convert To Textures
	{
		int Status = FALSE;									// Status Indicator
		AUX_RGBImageRec* TextureImage[2];					// Create Storage Space For The Textures
		memset( TextureImage, 0, sizeof( void* ) * 2 );			// Set The Pointer To NULL

		if ( (TextureImage[0] = LoadBMP( "Data/Font.bmp" )) &&	// Load The Font
			(TextureImage[1] = LoadBMP( "Data/Image.bmp" )) )	// Load Background Image
		{
			Status = TRUE;									// Set The Status To TRUE

			glGenTextures( 2, &texture[0] );					// Create The Texture

			for ( loop1 = 0; loop1 < 2; loop1++ )					// Loop Through 2 Textures
			{
				glBindTexture( GL_TEXTURE_2D, texture[loop1] );
				glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[loop1]->sizeX, TextureImage[loop1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[loop1]->data );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			}

			for ( loop1 = 0; loop1 < 2; loop1++ )					// Loop Through 2 Textures
			{
				if ( TextureImage[loop1] )					// If Texture Exists	
				{
					if ( TextureImage[loop1]->data )			// If Texture Image Exists
					{
						free( TextureImage[loop1]->data );	// Free The Texture Image Memory
					}
					free( TextureImage[loop1] );				// Free The Image Structure
				}
			}
		}
		return Status;											// Return The Status
	}

	GLvoid Lesson21::BuildFont( GLvoid )									// Build Our Font Display List
	{
		base = glGenLists( 256 );									// Creating 256 Display Lists
		glBindTexture( GL_TEXTURE_2D, texture[0] );				// Select Our Font Texture
		for ( loop1 = 0; loop1 < 256; loop1++ )						// Loop Through All 256 Lists
		{
			float cx = float( loop1 % 16 ) / 16.0f;						// X Position Of Current Character
			float cy = float( loop1 / 16 ) / 16.0f;						// Y Position Of Current Character

			glNewList( base + loop1, GL_COMPILE );					// Start Building A List
			glBegin( GL_QUADS );								// Use A Quad For Each Character
			glTexCoord2f( cx, 1.0f - cy - 0.0625f );			// Texture Coord (Bottom Left)
			glVertex2d( 0, 16 );							// Vertex Coord (Bottom Left)
			glTexCoord2f( cx + 0.0625f, 1.0f - cy - 0.0625f );	// Texture Coord (Bottom Right)
			glVertex2i( 16, 16 );							// Vertex Coord (Bottom Right)
			glTexCoord2f( cx + 0.0625f, 1.0f - cy );			// Texture Coord (Top Right)
			glVertex2i( 16, 0 );							// Vertex Coord (Top Right)
			glTexCoord2f( cx, 1.0f - cy );					// Texture Coord (Top Left)
			glVertex2i( 0, 0 );							// Vertex Coord (Top Left)
			glEnd();										// Done Building Our Quad (Character)
			glTranslated( 15, 0, 0 );							// Move To The Right Of The Character
			glEndList();										// Done Building The Display List
		}														// Loop Until All 256 Are Built
	}

	GLvoid Lesson21::KillFont( GLvoid )										// Delete The Font From Memory
	{
		glDeleteLists( base, 256 );								// Delete All 256 Display Lists
	}

	GLvoid Lesson21::glPrint( GLint x, GLint y, int set, const char* fmt, ... )	// Where The Printing Happens
	{
		char		text[256];									// Holds Our String
		va_list		ap;											// Pointer To List Of Arguments

		if ( fmt == NULL )										// If There's No Text
			return;												// Do Nothing

		va_start( ap, fmt );										// Parses The String For Variables
		vsprintf_s( text, fmt, ap );							// And Converts Symbols To Actual Numbers
		va_end( ap );												// Results Are Stored In Text

		if ( set > 1 )												// Did User Choose An Invalid Character Set?
		{
			set = 1;												// If So, Select Set 1 (Italic)
		}
		glEnable( GL_TEXTURE_2D );								// Enable Texture Mapping
		glLoadIdentity();										// Reset The Modelview Matrix
		glTranslated( x, y, 0 );									// Position The Text (0,0 - Bottom Left)
		glListBase( base - 32 + (128 * set) );							// Choose The Font Set (0 or 1)

		if ( set == 0 )												// If Set 0 Is Being Used Enlarge Font
		{
			glScalef( 1.5f, 2.0f, 1.0f );							// Enlarge Font Width And Height
		}

		glCallLists( strlen( text ), GL_UNSIGNED_BYTE, text );		// Write The Text To The Screen
		glDisable( GL_TEXTURE_2D );								// Disable Texture Mapping
	}

	GLvoid Lesson21::ReSizeGLScene( GLsizei width, GLsizei height )			// Resize And Initialize The GL Window
	{
		if ( height == 0 )											// Prevent A Divide By Zero By
		{
			height = 1;											// Making Height Equal One
		}

		glViewport( 0, 0, width, height );							// Reset The Current Viewport

		glMatrixMode( GL_PROJECTION );							// Select The Projection Matrix
		glLoadIdentity();										// Reset The Projection Matrix

		glOrtho( 0.0f, width, height, 0.0f, -1.0f, 1.0f );				// Create Ortho 640x480 View (0,0 At Top Left)

		glMatrixMode( GL_MODELVIEW );								// Select The Modelview Matrix
		glLoadIdentity();										// Reset The Modelview Matrix
	}

	int Lesson21::InitGL( GLvoid )											// All Setup For OpenGL Goes Here
	{
		if ( !LoadGLTextures() )									// Jump To Texture Loading Routine
		{
			return FALSE;										// If Texture Didn't Load Return FALSE
		}

		BuildFont();											// Build The Font

		glShadeModel( GL_SMOOTH );								// Enable Smooth Shading
		glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );					// Black Background
		glClearDepth( 1.0f );										// Depth Buffer Setup
		glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );					// Set Line Antialiasing
		glEnable( GL_BLEND );										// Enable Blending
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );		// Type Of Blending To Use
		return TRUE;											// Initialization Went OK
	}

	int Lesson21::DrawGLScene( GLvoid )										// Here's Where We Do All The Drawing
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );		// Clear Screen And Depth Buffer
		glBindTexture( GL_TEXTURE_2D, texture[0] );				// Select Our Font Texture
		glColor3f( 1.0f, 0.5f, 1.0f );								// Set Color To Purple
		glPrint( 207, 24, 0, "GRID CRAZY" );							// Write GRID CRAZY On The Screen
		glColor3f( 1.0f, 1.0f, 0.0f );								// Set Color To Yellow
		glPrint( 20, 20, 1, "Level:%2i", level2 );					// Write Actual Level Stats
		glPrint( 20, 40, 1, "Stage:%2i", stage );						// Write Stage Stats

		if ( gameover )											// Is The Game Over?
		{
			glColor3ub( rand() % 255, rand() % 255, rand() % 255 );		// Pick A Random Color
			glPrint( 472, 20, 1, "GAME OVER" );						// Write GAME OVER To The Screen
			glPrint( 456, 40, 1, "PRESS SPACE" );					// Write PRESS SPACE To The Screen
		}

		for ( loop1 = 0; loop1 < lives - 1; loop1++ )					// Loop Through Lives Minus Current Life
		{
			glLoadIdentity();									// Reset The View
			glTranslatef( 490 + (loop1 * 40.0f), 40.0f, 0.0f );			// Move To The Right Of Our Title Text
			glRotatef( -player.spin, 0.0f, 0.0f, 1.0f );				// Rotate Counter Clockwise
			glColor3f( 0.0f, 1.0f, 0.0f );							// Set Player Color To Light Green
			glBegin( GL_LINES );									// Start Drawing Our Player Using Lines
			glVertex2d( -5, -5 );								// Top Left Of Player
			glVertex2d( 5, 5 );								// Bottom Right Of Player
			glVertex2d( 5, -5 );								// Top Right Of Player
			glVertex2d( -5, 5 );								// Bottom Left Of Player
			glEnd();											// Done Drawing The Player
			glRotatef( -player.spin * 0.5f, 0.0f, 0.0f, 1.0f );		// Rotate Counter Clockwise
			glColor3f( 0.0f, 0.75f, 0.0f );							// Set Player Color To Dark Green
			glBegin( GL_LINES );									// Start Drawing Our Player Using Lines
			glVertex2d( -7, 0 );								// Left Center Of Player
			glVertex2d( 7, 0 );								// Right Center Of Player
			glVertex2d( 0, -7 );								// Top Center Of Player
			glVertex2d( 0, 7 );								// Bottom Center Of Player
			glEnd();											// Done Drawing The Player
		}

		filled = TRUE;											// Set Filled To True Before Testing
		glLineWidth( 2.0f );										// Set Line Width For Cells To 2.0f
		glDisable( GL_LINE_SMOOTH );								// Disable Antialiasing
		glLoadIdentity();										// Reset The Current Modelview Matrix
#pragma warning ( disable : 26451 )
		for ( loop1 = 0; loop1 < 11; loop1++ )						// Loop From Left To Right
		{
			for ( loop2 = 0; loop2 < 11; loop2++ )					// Loop From Top To Bottom
			{
				glColor3f( 0.0f, 0.5f, 1.0f );						// Set Line Color To Blue
				if ( hline[loop1][loop2] )						// Has The Horizontal Line Been Traced
				{
					glColor3f( 1.0f, 1.0f, 1.0f );					// If So, Set Line Color To White
				}

				if ( loop1 < 10 )									// Dont Draw To Far Right
				{
					if ( !hline[loop1][loop2] )					// If A Horizontal Line Isn't Filled
					{
						filled = FALSE;							// filled Becomes False
					}
					glBegin( GL_LINES );							// Start Drawing Horizontal Cell Borders
					glVertex2d( 20 + (loop1 * 60), 70 + (loop2 * 40) );// Left Side Of Horizontal Line
					glVertex2d( 80 + (loop1 * 60), 70 + (loop2 * 40) );// Right Side Of Horizontal Line
					glEnd();									// Done Drawing Horizontal Cell Borders
				}

				glColor3f( 0.0f, 0.5f, 1.0f );						// Set Line Color To Blue
				if ( vline[loop1][loop2] )						// Has The Horizontal Line Been Traced
				{
					glColor3f( 1.0f, 1.0f, 1.0f );					// If So, Set Line Color To White
				}
				if ( loop2 < 10 )									// Dont Draw To Far Down
				{
					if ( !vline[loop1][loop2] )					// If A Verticle Line Isn't Filled
					{
						filled = FALSE;							// filled Becomes False
					}
					glBegin( GL_LINES );							// Start Drawing Verticle Cell Borders
					glVertex2d( 20 + (loop1 * 60), 70 + (loop2 * 40) );// Left Side Of Horizontal Line
					glVertex2d( 20 + (loop1 * 60), 110 + (loop2 * 40) );// Right Side Of Horizontal Line
					glEnd();									// Done Drawing Verticle Cell Borders
				}

				glEnable( GL_TEXTURE_2D );						// Enable Texture Mapping
				glColor3f( 1.0f, 1.0f, 1.0f );						// Bright White Color
				glBindTexture( GL_TEXTURE_2D, texture[1] );		// Select The Tile Image
				if ( (loop1 < 10) && (loop2 < 10) )					// If In Bounds, Fill In Traced Boxes
				{
					// Are All Sides Of The Box Traced?
					if ( hline[loop1][loop2] && hline[loop1][loop2 + 1] && vline[loop1][loop2] && vline[loop1 + 1][loop2] )
					{
						glBegin( GL_QUADS );						// Draw A Textured Quad
						glTexCoord2f( float( loop1 / 10.0f ) + 0.1f, 1.0f - (float( loop2 / 10.0f )) );
						glVertex2d( 20 + (loop1 * 60) + 59, (70 + loop2 * 40 + 1) );	// Top Right
						glTexCoord2f( float( loop1 / 10.0f ), 1.0f - (float( loop2 / 10.0f )) );
						glVertex2d( 20 + (loop1 * 60) + 1, (70 + loop2 * 40 + 1) );	// Top Left
						glTexCoord2f( float( loop1 / 10.0f ), 1.0f - (float( loop2 / 10.0f ) + 0.1f) );
						glVertex2d( 20 + (loop1 * 60) + 1, (70 + loop2 * 40) + 39 );	// Bottom Left
						glTexCoord2f( float( loop1 / 10.0f ) + 0.1f, 1.0f - (float( loop2 / 10.0f ) + 0.1f) );
						glVertex2d( 20 + (loop1 * 60) + 59, (70 + loop2 * 40) + 39 );	// Bottom Right
						glEnd();								// Done Texturing The Box
					}
				}
				glDisable( GL_TEXTURE_2D );						// Disable Texture Mapping
			}
		}
#pragma warning ( default : 26451 )
		glLineWidth( 1.0f );										// Set The Line Width To 1.0f

		if ( anti )												// Is Anti TRUE?
		{
			glEnable( GL_LINE_SMOOTH );							// If So, Enable Antialiasing
		}

		if ( hourglass.fx == 1 )									// If fx=1 Draw The Hourglass
		{
			glLoadIdentity();									// Reset The Modelview Matrix
			glTranslatef( 20.0f + (hourglass.x * 60), 70.0f + (hourglass.y * 40), 0.0f );	// Move To The Fine Hourglass Position
			glRotatef( hourglass.spin, 0.0f, 0.0f, 1.0f );			// Rotate Clockwise
			glColor3ub( rand() % 255, rand() % 255, rand() % 255 );		// Set Hourglass Color To Random Color
			glBegin( GL_LINES );									// Start Drawing Our Hourglass Using Lines
			glVertex2d( -5, -5 );								// Top Left Of Hourglass
			glVertex2d( 5, 5 );								// Bottom Right Of Hourglass
			glVertex2d( 5, -5 );								// Top Right Of Hourglass
			glVertex2d( -5, 5 );								// Bottom Left Of Hourglass
			glVertex2d( -5, 5 );								// Bottom Left Of Hourglass
			glVertex2d( 5, 5 );								// Bottom Right Of Hourglass
			glVertex2d( -5, -5 );								// Top Left Of Hourglass
			glVertex2d( 5, -5 );								// Top Right Of Hourglass
			glEnd();											// Done Drawing The Hourglass
		}

		glLoadIdentity();										// Reset The Modelview Matrix
		glTranslatef( player.fx + 20.0f, player.fy + 70.0f, 0.0f );		// Move To The Fine Player Position
		glRotatef( player.spin, 0.0f, 0.0f, 1.0f );					// Rotate Clockwise
		glColor3f( 0.0f, 1.0f, 0.0f );								// Set Player Color To Light Green
		glBegin( GL_LINES );										// Start Drawing Our Player Using Lines
		glVertex2d( -5, -5 );									// Top Left Of Player
		glVertex2d( 5, 5 );									// Bottom Right Of Player
		glVertex2d( 5, -5 );									// Top Right Of Player
		glVertex2d( -5, 5 );									// Bottom Left Of Player
		glEnd();												// Done Drawing The Player
		glRotatef( player.spin * 0.5f, 0.0f, 0.0f, 1.0f );				// Rotate Clockwise
		glColor3f( 0.0f, 0.75f, 0.0f );								// Set Player Color To Dark Green
		glBegin( GL_LINES );										// Start Drawing Our Player Using Lines
		glVertex2d( -7, 0 );									// Left Center Of Player
		glVertex2d( 7, 0 );									// Right Center Of Player
		glVertex2d( 0, -7 );									// Top Center Of Player
		glVertex2d( 0, 7 );									// Bottom Center Of Player
		glEnd();												// Done Drawing The Player

		for ( loop1 = 0; loop1 < (stage * level); loop1++ )				// Loop To Draw Enemies
		{
			glLoadIdentity();									// Reset The Modelview Matrix
			glTranslatef( enemy[loop1].fx + 20.0f, enemy[loop1].fy + 70.0f, 0.0f );
			glColor3f( 1.0f, 0.5f, 0.5f );							// Make Enemy Body Pink
			glBegin( GL_LINES );									// Start Drawing Enemy
			glVertex2d( 0, -7 );								// Top Point Of Body
			glVertex2d( -7, 0 );								// Left Point Of Body
			glVertex2d( -7, 0 );								// Left Point Of Body
			glVertex2d( 0, 7 );								// Bottom Point Of Body
			glVertex2d( 0, 7 );								// Bottom Point Of Body
			glVertex2d( 7, 0 );								// Right Point Of Body
			glVertex2d( 7, 0 );								// Right Point Of Body
			glVertex2d( 0, -7 );								// Top Point Of Body
			glEnd();											// Done Drawing Enemy Body
			glRotatef( enemy[loop1].spin, 0.0f, 0.0f, 1.0f );		// Rotate The Enemy Blade
			glColor3f( 1.0f, 0.0f, 0.0f );							// Make Enemy Blade Red
			glBegin( GL_LINES );									// Start Drawing Enemy Blade
			glVertex2d( -7, -7 );								// Top Left Of Enemy
			glVertex2d( 7, 7 );								// Bottom Right Of Enemy
			glVertex2d( -7, 7 );								// Bottom Left Of Enemy
			glVertex2d( 7, -7 );								// Top Right Of Enemy
			glEnd();											// Done Drawing Enemy Blade
		}
		return TRUE;											// Everything Went OK
	}

	int Lesson21::CleanGL( GLvoid )									// Properly Kill The Window
	{
		KillFont();												// Kill The Font We Built
		return TRUE;
	}

	
	void Lesson21::Update( DWORD milliseconds, const bool keys[] )													// If There Are No Messages
	{
		float start = TimerGetTime();							// Grab Timer Value Before We Draw

		while ( TimerGetTime() < start + float( steps[adjust] * 2.0f ) ) {}	// Waste Cycles On Fast Systems

		if ( keys['A'] && !ap )								// If 'A' Key Is Pressed And Not Held
		{
			ap = TRUE;										// ap Becomes TRUE
			anti = !anti;										// Toggle Antialiasing
		}
		if ( !keys['A'] )										// If 'A' Key Has Been Released
		{
			ap = FALSE;										// ap Becomes FALSE
		}

		if ( !gameover && active )							// If Game Isn't Over And Programs Active Move Objects
		{
			for ( loop1 = 0; loop1 < (stage * level); loop1++ )		// Loop Through The Different Stages
			{
				if ( (enemy[loop1].x < player.x) && (enemy[loop1].fy == enemy[loop1].y * 40) )
				{
					enemy[loop1].x++;						// Move The Enemy Right
				}

				if ( (enemy[loop1].x > player.x) && (enemy[loop1].fy == enemy[loop1].y * 40) )
				{
					enemy[loop1].x--;						// Move The Enemy Left
				}

				if ( (enemy[loop1].y < player.y) && (enemy[loop1].fx == enemy[loop1].x * 60) )
				{
					enemy[loop1].y++;						// Move The Enemy Down
				}

				if ( (enemy[loop1].y > player.y) && (enemy[loop1].fx == enemy[loop1].x * 60) )
				{
					enemy[loop1].y--;						// Move The Enemy Up
				}

				if ( delay > (3 - level) && (hourglass.fx != 2) )	// If Our Delay Is Done And Player Doesn't Have Hourglass
				{
					delay = 0;								// Reset The Delay Counter Back To Zero
					for ( loop2 = 0; loop2 < (stage * level); loop2++ )	// Loop Through All The Enemies
					{
						if ( enemy[loop2].fx < enemy[loop2].x * 60 )	// Is Fine Position On X Axis Lower Than Intended Position?
						{
							enemy[loop2].fx += steps[adjust];	// If So, Increase Fine Position On X Axis
							enemy[loop2].spin += steps[adjust];	// Spin Enemy Clockwise
						}
						if ( enemy[loop2].fx > enemy[loop2].x * 60 )	// Is Fine Position On X Axis Higher Than Intended Position?
						{
							enemy[loop2].fx -= steps[adjust];	// If So, Decrease Fine Position On X Axis
							enemy[loop2].spin -= steps[adjust];	// Spin Enemy Counter Clockwise
						}
						if ( enemy[loop2].fy < enemy[loop2].y * 40 )	// Is Fine Position On Y Axis Lower Than Intended Position?
						{
							enemy[loop2].fy += steps[adjust];	// If So, Increase Fine Position On Y Axis
							enemy[loop2].spin += steps[adjust];	// Spin Enemy Clockwise
						}
						if ( enemy[loop2].fy > enemy[loop2].y * 40 )	// Is Fine Position On Y Axis Higher Than Intended Position?
						{
							enemy[loop2].fy -= steps[adjust];	// If So, Decrease Fine Position On Y Axis
							enemy[loop2].spin -= steps[adjust];	// Spin Enemy Counter Clockwise
						}
					}
				}

				// Are Any Of The Enemies On Top Of The Player?
				if ( (enemy[loop1].fx == player.fx) && (enemy[loop1].fy == player.fy) )
				{
					lives--;								// If So, Player Loses A Life

					if ( lives == 0 )							// Are We Out Of Lives?
					{
						gameover = TRUE;						// If So, gameover Becomes TRUE
					}

					ResetObjects();							// Reset Player / Enemy Positions
					PlaySound( _T( "Data/Die.wav" ), NULL, SND_SYNC );	// Play The Death Sound
				}
			}

			if ( keys[VK_RIGHT] && (player.x < 10) && (player.fx == player.x * 60) && (player.fy == player.y * 40) )
			{
				hline[player.x][player.y] = TRUE;				// Mark The Current Horizontal Border As Filled
				player.x++;									// Move The Player Right
			}
			if ( keys[VK_LEFT] && (player.x > 0) && (player.fx == player.x * 60) && (player.fy == player.y * 40) )
			{
				player.x--;									// Move The Player Left
				hline[player.x][player.y] = TRUE;				// Mark The Current Horizontal Border As Filled
			}
			if ( keys[VK_DOWN] && (player.y < 10) && (player.fx == player.x * 60) && (player.fy == player.y * 40) )
			{
				vline[player.x][player.y] = TRUE;				// Mark The Current Verticle Border As Filled
				player.y++;									// Move The Player Down
			}
			if ( keys[VK_UP] && (player.y > 0) && (player.fx == player.x * 60) && (player.fy == player.y * 40) )
			{
				player.y--;									// Move The Player Up
				vline[player.x][player.y] = TRUE;				// Mark The Current Verticle Border As Filled
			}

			if ( player.fx < player.x * 60 )						// Is Fine Position On X Axis Lower Than Intended Position?
			{
				player.fx += steps[adjust];					// If So, Increase The Fine X Position
			}
			if ( player.fx > player.x * 60 )						// Is Fine Position On X Axis Greater Than Intended Position?
			{
				player.fx -= steps[adjust];					// If So, Decrease The Fine X Position
			}
			if ( player.fy < player.y * 40 )						// Is Fine Position On Y Axis Lower Than Intended Position?
			{
				player.fy += steps[adjust];					// If So, Increase The Fine Y Position
			}
			if ( player.fy > player.y * 40 )						// Is Fine Position On Y Axis Lower Than Intended Position?
			{
				player.fy -= steps[adjust];					// If So, Decrease The Fine Y Position
			}
		}
		else												// Otherwise
		{
			if ( keys[' '] )									// If Spacebar Is Being Pressed
			{
				gameover = FALSE;								// gameover Becomes FALSE
				filled = TRUE;								// filled Becomes TRUE
				level = 1;									// Starting Level Is Set Back To One
				level2 = 1;									// Displayed Level Is Also Set To One
				stage = 0;									// Game Stage Is Set To Zero
				lives = 5;									// Lives Is Set To Five
			}
		}

		if ( filled )											// Is The Grid Filled In?
		{
			PlaySound( _T( "Data/Complete.wav" ), NULL, SND_SYNC );	// If So, Play The Level Complete Sound
			stage++;										// Increase The Stage
			if ( stage > 3 )									// Is The Stage Higher Than 3?
			{
				stage = 1;									// If So, Set The Stage To One
				level++;									// Increase The Level
				level2++;									// Increase The Displayed Level
				if ( level > 3 )								// Is The Level Greater Than 3?
				{
					level = 3;								// If So, Set The Level To 3
					lives++;								// Give The Player A Free Life
					if ( lives > 5 )							// Does The Player Have More Than 5 Lives?
					{
						lives = 5;							// If So, Set Lives To Five
					}
				}
			}

			ResetObjects();									// Reset Player / Enemy Positions

			for ( loop1 = 0; loop1 < 11; loop1++ )				// Loop Through The Grid X Coordinates
			{
				for ( loop2 = 0; loop2 < 11; loop2++ )			// Loop Through The Grid Y Coordinates
				{
					if ( loop1 < 10 )							// If X Coordinate Is Less Than 10
					{
						hline[loop1][loop2] = FALSE;			// Set The Current Horizontal Value To FALSE
					}
					if ( loop2 < 10 )							// If Y Coordinate Is Less Than 10
					{
						vline[loop1][loop2] = FALSE;			// Set The Current Vertical Value To FALSE
					}
				}
			}
		}

		// If The Player Hits The Hourglass While It's Being Displayed On The Screen
		if ( (player.fx == hourglass.x * 60) && (player.fy == hourglass.y * 40) && (hourglass.fx == 1) )
		{
			// Play Freeze Enemy Sound
			PlaySound( _T( "Data/freeze.wav" ), NULL, SND_ASYNC | SND_LOOP );
			hourglass.fx = 2;									// Set The hourglass fx Variable To Two
			hourglass.fy = 0;									// Set The hourglass fy Variable To Zero
		}

		player.spin += 0.5f * steps[adjust];					// Spin The Player Clockwise
		if ( player.spin > 360.0f )								// Is The spin Value Greater Than 360?
		{
			player.spin -= 360;								// If So, Subtract 360
		}

		hourglass.spin -= 0.25f * steps[adjust];				// Spin The Hourglass Counter Clockwise
		if ( hourglass.spin < 0.0f )							// Is The spin Value Less Than 0?
		{
			hourglass.spin += 360.0f;							// If So, Add 360
		}

		hourglass.fy += steps[adjust];						// Increase The hourglass fy Variable
		if ( (hourglass.fx == 0) && (hourglass.fy > 6000 / level) )	// Is The hourglass fx Variable Equal To 0 And The fy
		{													// Variable Greater Than 6000 Divided By The Current Level?
			PlaySound( _T( "Data/hourglass.wav" ), NULL, SND_ASYNC );	// If So, Play The Hourglass Appears Sound
			hourglass.x = rand() % 10 + 1;						// Give The Hourglass A Random X Value
			hourglass.y = rand() % 11;							// Give The Hourglass A Random Y Value
			hourglass.fx = 1;									// Set hourglass fx Variable To One (Hourglass Stage)
			hourglass.fy = 0;									// Set hourglass fy Variable To Zero (Counter)
		}

		if ( (hourglass.fx == 1) && (hourglass.fy > 6000 / level) )	// Is The hourglass fx Variable Equal To 1 And The fy
		{													// Variable Greater Than 6000 Divided By The Current Level?
			hourglass.fx = 0;									// If So, Set fx To Zero (Hourglass Will Vanish)
			hourglass.fy = 0;									// Set fy to Zero (Counter Is Reset)
		}

		if ( (hourglass.fx == 2) && (hourglass.fy > 500 + (500 * level)) )	// Is The hourglass fx Variable Equal To 2 And The fy
		{													// Variable Greater Than 500 Plus 500 Times The Current Level?
			PlaySound( NULL, NULL, 0 );						// If So, Kill The Freeze Sound
			hourglass.fx = 0;									// Set hourglass fx Variable To Zero
			hourglass.fy = 0;									// Set hourglass fy Variable To Zero
		}

		delay++;											// Increase The Enemy Delay Counter
	}
}