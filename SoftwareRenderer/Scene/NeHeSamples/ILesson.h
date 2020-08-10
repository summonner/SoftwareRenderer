#pragma once
#include "../gl/glAdapter.h"

namespace NeHe
{
	class ILesson abstract
	{
	public:
		virtual ~ILesson() {};

		virtual int CleanGL( GLvoid ) { return TRUE; };
		virtual GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) abstract;
		virtual int DrawGLScene( GLvoid ) abstract;
		virtual int InitGL( GLvoid ) abstract;
		virtual void Update( DWORD milliseconds, const bool keys[] ) {};
	};

	AUX_RGBImageRec* LoadBMP( LPCSTR filePath );
}