#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson11 final : public ILesson
	{
	public:
		Lesson11();
		~Lesson11() override;

		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;

	private:
		int LoadGLTextures();

	private:
		float points[45][45][3];    // The Array For The Points On The Grid Of Our "Wave"
		int wiggle_count = 0;		// Counter Used To Control How Fast Flag Waves

		GLfloat	xrot;				// X Rotation ( NEW )
		GLfloat	yrot;				// Y Rotation ( NEW )
		GLfloat	zrot;				// Z Rotation ( NEW )
		GLfloat hold;				// Temporarily Holds A Floating Point Value

		GLuint	texture[1];			// Storage For One Texture ( NEW )
	};
}