#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson24 final : public ILesson
	{
	private:
		typedef struct												// Create A Structure
		{
			GLubyte* imageData;										// Image Data (Up To 32 Bits)
			GLuint	bpp;											// Image Color Depth In Bits Per Pixel.
			GLuint	width;											// Image Width
			GLuint	height;											// Image Height
			GLuint	texID;											// Texture ID Used To Select A Texture
		} TextureImage;												// Structure Name

	public:
		Lesson24();
		~Lesson24() override;

		void Update( DWORD milliseconds, const bool keys[] ) override;
		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		int CleanGL( GLvoid ) override;

	private:
		bool LoadTGA( TextureImage* texture, const char* filename );
		GLvoid BuildFont( GLvoid );
		GLvoid KillFont( GLvoid );
		GLvoid glPrint( GLint x, GLint y, int set, const char* fmt, ... );

	private:
		int			scroll;											// Used For Scrolling The Screen
		int			maxtokens;										// Keeps Track Of The Number Of Extensions Supported
		int			swidth;											// Scissor Width
		int			sheight;										// Scissor Height

		GLuint		base;											// Base Display List For The Font

		TextureImage textures[1];									// Storage For One Texture

	};
}