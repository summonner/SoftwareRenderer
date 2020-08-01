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

		int CleanGL( GLvoid ) override;
		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;

	private:
		int LoadGLTextures();

	private:
		GLfloat	xrot;				// X Rotation ( NEW )
		GLfloat	yrot;				// Y Rotation ( NEW )
		GLfloat	zrot;				// Z Rotation ( NEW )

		GLuint	texture[1];			// Storage For One Texture ( NEW )
	};
}