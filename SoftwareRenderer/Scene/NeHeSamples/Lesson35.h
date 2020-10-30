#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson35 final : public ILesson
	{
	public:
		Lesson35();
		~Lesson35() override;

		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		int CleanGL( GLvoid ) override;
		void Update( DWORD milliseconds, bool keys[] ) override;
		const char* GetDescription() const override;

	private:
		void flipIt( void* buffer );
		void OpenAVI( LPCTSTR szFile );
		void GrabAVIFrame( int frame );
		void CloseAVI( void );

	private:
		// User Defined Variables
		float		angle{};												// Used For Rotation
		int			next{};												// Used For Animation
		int			frame = 0;											// Frame Counter
		int			effect{};												// Current Effect
		bool		sp{};													// Space Bar Pressed?
		bool		env = TRUE;											// Environment Mapping (Default On)
		bool		ep{};													// 'E' Pressed?
		bool		bg = TRUE;											// Background (Default On)
		bool		bp{};													// 'B' Pressed?

		AVISTREAMINFO		psi{};										// Pointer To A Structure Containing Stream Info
		PAVISTREAM			pavi{};										// Handle To An Open Stream
		PGETFRAME			pgf{};										// Pointer To A GetFrame Object
		BITMAPINFOHEADER	bmih{};										// Header Information For DrawDibDraw Decoding
		long				lastframe{};									// Last Frame Of The Stream
		int					width{};										// Video Width
		int					height{};										// Video Height
		char* pdata{};										// Pointer To Texture Data
		int					mpf{};										// Will Hold Rough Milliseconds Per Frame

		GLUquadricObj* quadratic{};										// Storage For Our Quadratic Objects

		HDRAWDIB hdd{};													// Handle For Our Dib
		HBITMAP hBitmap{};												// Handle To A Device Dependant Bitmap
		HDC hdc = CreateCompatibleDC( 0 );								// Creates A Compatible Device Context
		unsigned char* data = 0;										// Pointer To Our Resized Image

	};
}