#pragma once
#include "ILesson.h"

#define LESSON Lesson6

namespace NeHe
{
	class LESSON : public ILesson
	{
	public:
		LESSON();
		~LESSON() override;

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