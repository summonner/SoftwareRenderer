#pragma once
#include "../gl/glAdapter.h"

namespace NeHe
{
	class ILesson abstract
	{
	public:
		virtual ~ILesson() {};

		virtual int CleanGL( GLvoid ) abstract;
		virtual int DrawGLScene( GLvoid ) abstract;
		virtual int InitGL( GLvoid ) abstract;
	};

	AUX_RGBImageRec* LoadBMP( LPCSTR filePath );
}