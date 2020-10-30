#include "framework.h"
#include "Lesson35.h"
#pragma comment( lib, "vfw32.lib" )								// Search For VFW32.lib While Linking

namespace NeHe
{
	Lesson35::Lesson35()
	{
	}

	Lesson35::~Lesson35()
	{
	}

	void Lesson35::flipIt( void* buffer )										// Flips The Red And Blue Bytes (256x256)
	{
		void* b = buffer;											// Pointer To The Buffer
		__asm														// Assembler Code To Follow
		{
			mov ecx, 256 * 256										// Counter Set To Dimensions Of Our Memory Block
			mov ebx, b												// Points ebx To Our Data (b)
			label :													// Label Used For Looping
			mov al, [ebx + 0]										// Loads Value At ebx Into al
				mov ah, [ebx + 2]										// Loads Value At ebx+2 Into ah
				mov[ebx + 2], al										// Stores Value In al At ebx+2
				mov[ebx + 0], ah										// Stores Value In ah At ebx

				add ebx, 3											// Moves Through The Data By 3 Bytes
				dec ecx												// Decreases Our Loop Counter
				jnz label											// If Not Zero Jump Back To Label
		}
	}

	void Lesson35::OpenAVI( LPCTSTR szFile )										// Opens An AVI File (szFile)
	{
		TCHAR	title[100];											// Will Hold The Modified Window Title

		AVIFileInit();												// Opens The AVIFile Library

		// Opens The AVI Stream
		if ( AVIStreamOpenFromFile( &pavi, szFile, streamtypeVIDEO, 0, OF_READ, NULL ) != 0 )
		{
			// An Error Occurred Opening The Stream
			MessageBox( HWND_DESKTOP, _T("Failed To Open The AVI Stream"), _T("Error"), MB_OK | MB_ICONEXCLAMATION );
		}

		AVIStreamInfo( pavi, &psi, sizeof( psi ) );						// Reads Information About The Stream Into psi
		width = psi.rcFrame.right - psi.rcFrame.left;					// Width Is Right Side Of Frame Minus Left
		height = psi.rcFrame.bottom - psi.rcFrame.top;					// Height Is Bottom Of Frame Minus Top

		lastframe = AVIStreamLength( pavi );							// The Last Frame Of The Stream

		mpf = AVIStreamSampleToTime( pavi, lastframe ) / lastframe;		// Calculate Rough Milliseconds Per Frame

		bmih.biSize = sizeof( BITMAPINFOHEADER );					// Size Of The BitmapInfoHeader
		bmih.biPlanes = 1;											// Bitplanes	
		bmih.biBitCount = 24;										// Bits Format We Want (24 Bit, 3 Bytes)
		bmih.biWidth = 256;											// Width We Want (256 Pixels)
		bmih.biHeight = 256;										// Height We Want (256 Pixels)
		bmih.biCompression = BI_RGB;								// Requested Mode = RGB

		hBitmap = CreateDIBSection( hdc, (BITMAPINFO*)(&bmih), DIB_RGB_COLORS, (void**)(&data), NULL, NULL );
		if ( hBitmap == 0 )
		{
			return;
		}

		SelectObject( hdc, hBitmap );								// Select hBitmap Into Our Device Context (hdc)

		pgf = AVIStreamGetFrameOpen( pavi, NULL );						// Create The PGETFRAME	Using Our Request Mode
		if ( pgf == NULL )
		{
			// An Error Occurred Opening The Frame
			MessageBox( HWND_DESKTOP, _T("Failed To Open The AVI Frame"), _T("Error"), MB_OK | MB_ICONEXCLAMATION );
		}

		// Information For The Title Bar (Width / Height / Last Frame)
		wsprintf( title, _T("NeHe's AVI Player: Width: %d, Height: %d, Frames: %d"), width, height, lastframe );
		//SetWindowText( g_window->hWnd, title );						// Modify The Title Bar
	}

	void Lesson35::GrabAVIFrame( int frame )									// Grabs A Frame From The Stream
	{
		LPBITMAPINFOHEADER lpbi;									// Holds The Bitmap Header Information
		lpbi = (LPBITMAPINFOHEADER)AVIStreamGetFrame( pgf, frame );	// Grab Data From The AVI Stream
		pdata = (char*)lpbi + lpbi->biSize + lpbi->biClrUsed * sizeof( RGBQUAD );	// Pointer To Data Returned By AVIStreamGetFrame

		// Convert Data To Requested Bitmap Format
		DrawDibDraw( hdd, hdc, 0, 0, 256, 256, lpbi, pdata, 0, 0, width, height, 0 );

		flipIt( data );												// Swap The Red And Blue Bytes (GL Compatability)

		// Update The Texture
		glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, 256, 256, GL_RGB, GL_UNSIGNED_BYTE, data );
	}

	void Lesson35::CloseAVI( void )												// Properly Closes The Avi File
	{
		DeleteObject( hBitmap );										// Delete The Device Dependant Bitmap Object
		DrawDibClose( hdd );											// Closes The DrawDib Device Context
		AVIStreamGetFrameClose( pgf );								// Deallocates The GetFrame Resources
		AVIStreamRelease( pavi );										// Release The Stream
		AVIFileExit();												// Release The File
	}

	int Lesson35::InitGL( GLvoid )					// Any GL Init Code & User Initialiazation Goes Here
	{
		// Start Of User Initialization
		angle = 0.0f;											// Set Starting Angle To Zero
		hdd = DrawDibOpen();										// Grab A Device Context For Our Dib
		glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );						// Black Background
		glClearDepth( 1.0f );										// Depth Buffer Setup
		glDepthFunc( GL_LEQUAL );									// The Type Of Depth Testing (Less Or Equal)
		glEnable( GL_DEPTH_TEST );									// Enable Depth Testing
		glShadeModel( GL_SMOOTH );									// Select Smooth Shading
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );			// Set Perspective Calculations To Most Accurate

		quadratic = gluNewQuadric();									// Create A Pointer To The Quadric Object
		gluQuadricNormals( quadratic, GLU_SMOOTH );					// Create Smooth Normals 
		gluQuadricTexture( quadratic, GL_TRUE );						// Create Texture Coords 

		glEnable( GL_TEXTURE_2D );									// Enable Texture Mapping
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );	// Set Texture Max Filter
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );	// Set Texture Min Filter

		glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );		// Set The Texture Generation Mode For S To Sphere Mapping
		glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );		// Set The Texture Generation Mode For T To Sphere Mapping

		OpenAVI( _T("data/face2.avi") );									// Open The AVI File

		// Create The Texture
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, data );

		return TRUE;												// Return TRUE (Initialization Successful)
	}

	int Lesson35::CleanGL( GLvoid )										// Any User DeInitialization Goes Here
	{
		CloseAVI();													// Close The AVI File
		return TRUE;
	}
	
	const char* Lesson35::GetDescription() const
	{
		return "Space - Change Shape\n\
				B - Toggle Backgound\n\
				E - Toggle Environment Mapping";
	}

	void Lesson35::Update( DWORD milliseconds, bool keys[] )								// Perform Motion Updates Here
	{
		if ( (keys[' ']) && !sp )							// Is Space Being Pressed And Not Held?
		{
			sp = TRUE;												// Set sp To True
			effect++;												// Change Effects (Increase effect)
			if ( effect > 3 )											// Over Our Limit?
				effect = 0;											// Reset Back To 0
		}

		if ( !keys[' '] )									// Is Space Released?
			sp = FALSE;												// Set sp To False

		if ( (keys['B']) && !bp )							// Is 'B' Being Pressed And Not Held?
		{
			bp = TRUE;												// Set bp To True
			bg = !bg;													// Toggle Background Off/On
		}

		if ( !keys['B'] )									// Is 'B' Released?
			bp = FALSE;												// Set bp To False

		if ( (keys['E']) && !ep )							// Is 'E' Being Pressed And Not Held?
		{
			ep = TRUE;												// Set ep To True
			env = !env;												// Toggle Environment Mapping Off/On
		}

		if ( !keys['E'] )									// Is 'E' Released?
			ep = FALSE;												// Set ep To False

		angle += (float)(milliseconds) / 60.0f;						// Update angle Based On The Timer

		next += milliseconds;											// Increase next Based On The Timer
		frame = next / mpf;												// Calculate The Current Frame

		if ( frame >= lastframe )										// Are We At Or Past The Last Frame?
		{
			frame = 0;												// Reset The Frame Back To Zero (Start Of Video)
			next = 0;													// Reset The Animation Timer (next)
		}
	}

	int Lesson35::DrawGLScene( GLvoid )												// Draw Our Scene
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );		// Clear Screen And Depth Buffer

		GrabAVIFrame( frame );										// Grab A Frame From The AVI

		if ( bg )														// Is Background Visible?
		{
			glLoadIdentity();										// Reset The Modelview Matrix
			glBegin( GL_QUADS );										// Begin Drawing The Background (One Quad)
				// Front Face
			glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 11.0f, 8.3f, -20.0f );
			glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -11.0f, 8.3f, -20.0f );
			glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -11.0f, -8.3f, -20.0f );
			glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 11.0f, -8.3f, -20.0f );
			glEnd();												// Done Drawing The Background
		}

		glLoadIdentity();											// Reset The Modelview Matrix
		glTranslatef( 0.0f, 0.0f, -10.0f );							// Translate 10 Units Into The Screen

		if ( env )													// Is Environment Mapping On?
		{
			glEnable( GL_TEXTURE_GEN_S );								// Enable Texture Coord Generation For S (NEW)
			glEnable( GL_TEXTURE_GEN_T );								// Enable Texture Coord Generation For T (NEW)
		}

		glRotatef( angle * 2.3f, 1.0f, 0.0f, 0.0f );						// Throw In Some Rotations To Move Things Around A Bit
		glRotatef( angle * 1.8f, 0.0f, 1.0f, 0.0f );						// Throw In Some Rotations To Move Things Around A Bit
		glTranslatef( 0.0f, 0.0f, 2.0f );								// After Rotating Translate To New Position

		switch ( effect )												// Which Effect?
		{
		case 0:														// Effect 0 - Cube
			glRotatef( angle * 1.3f, 1.0f, 0.0f, 0.0f );				// Rotate On The X-Axis By angle
			glRotatef( angle * 1.1f, 0.0f, 1.0f, 0.0f );				// Rotate On The Y-Axis By angle
			glRotatef( angle * 1.2f, 0.0f, 0.0f, 1.0f );				// Rotate On The Z-Axis By angle
			glBegin( GL_QUADS );										// Begin Drawing A Cube
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
			glEnd();												// Done Drawing Our Cube
			break;													// Done Effect 0

		case 1:														// Effect 1 - Sphere
			glRotatef( angle * 1.3f, 1.0f, 0.0f, 0.0f );				// Rotate On The X-Axis By angle
			glRotatef( angle * 1.1f, 0.0f, 1.0f, 0.0f );				// Rotate On The Y-Axis By angle
			glRotatef( angle * 1.2f, 0.0f, 0.0f, 1.0f );				// Rotate On The Z-Axis By angle
			gluSphere( quadratic, 1.3f, 20, 20 );						// Draw A Sphere
			break;													// Done Drawing Sphere

		case 2:														// Effect 2 - Cylinder
			glRotatef( angle * 1.3f, 1.0f, 0.0f, 0.0f );				// Rotate On The X-Axis By angle
			glRotatef( angle * 1.1f, 0.0f, 1.0f, 0.0f );				// Rotate On The Y-Axis By angle
			glRotatef( angle * 1.2f, 0.0f, 0.0f, 1.0f );				// Rotate On The Z-Axis By angle
			glTranslatef( 0.0f, 0.0f, -1.5f );							// Center The Cylinder
			gluCylinder( quadratic, 1.0f, 1.0f, 3.0f, 32, 32 );			// Draw A Cylinder
			break;													// Done Drawing Cylinder
		}

		if ( env )													// Environment Mapping Enabled?
		{
			glDisable( GL_TEXTURE_GEN_S );							// Disable Texture Coord Generation For S (NEW)
			glDisable( GL_TEXTURE_GEN_T );							// Disable Texture Coord Generation For T (NEW)
		}

		glFlush();													// Flush The GL Rendering Pipeline
		return TRUE;
	}
}