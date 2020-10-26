#pragma once
#include "../gl/glAdapter.h"

namespace NeHe
{
	class ILesson abstract
	{
	public:
		virtual ~ILesson() {};

		virtual int CleanGL( GLvoid ) { return TRUE; };
		virtual GLvoid ReSizeGLScene( GLsizei width, GLsizei height );
		virtual int DrawGLScene( GLvoid ) abstract;
		virtual int InitGL( GLvoid ) abstract;
		virtual void Update( DWORD milliseconds, const bool keys[] ) {};

		virtual const char* GetDescription() const { return nullptr; };

	protected:
		FILE* fopen( const char* filename, const char* mode );
		template<typename... Args>
		int sscanf( char const* const buffer, char const* const format, Args... args )
		{
			return sscanf_s( buffer, format, args... );
		}

		AUX_RGBImageRec* auxDIBImageLoad( LPCSTR filePath );
	};

	AUX_RGBImageRec* LoadBMP( LPCSTR filePath );
}