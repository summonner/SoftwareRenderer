#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson12 final : public ILesson
	{
	public:
		Lesson12();
		~Lesson12() override;

		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		int CleanGL( GLvoid ) override;

		void Update( DWORD milliseconds, const bool keys[] ) override;
		const char* GetDescription() const override;

	private:
		int LoadGLTextures();
		GLvoid BuildLists();


	private:
		GLuint	texture[1];			// Storage For 1 Texture
		GLuint	box;				// Storage For The Box Display List
		GLuint	top;				// Storage For The Top Display List
		GLuint	xloop;				// Loop For X Axis
		GLuint	yloop;				// Loop For Y Axis

		GLfloat	xrot;				// Rotates Cube On The X Axis
		GLfloat	yrot;				// Rotates Cube On The Y Axis
	};
}