#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson6 : public ILesson
	{
	public:
		Lesson6();
		~Lesson6() override;

		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;

	private:
		int LoadGLTextures();

	private:
		GLfloat	xrot;				// X Rotation ( NEW )
		GLfloat	yrot;				// Y Rotation ( NEW )
		GLfloat	zrot;				// Z Rotation ( NEW )

		GLuint	texture[1];			// Storage For One Texture ( NEW )
	};
}