#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson17 final : public ILesson
	{
	public:
		Lesson17();
		~Lesson17();

		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		int CleanGL( GLvoid ) override;

	private:
		int LoadGLTextures();
		GLvoid BuildFont( GLvoid );
		GLvoid KillFont( GLvoid );
		GLvoid glPrint( GLint x, GLint y, const char* string, int set );

	private:
		GLuint	base;				// Base Display List For The Font
		GLuint	texture[2];			// Storage For Our Font Texture
		GLuint	loop;				// Generic Loop Variable

		GLfloat	cnt1;				// 1st Counter Used To Move Text & For Coloring
		GLfloat	cnt2;				// 2nd Counter Used To Move Text & For Coloring
	};
}