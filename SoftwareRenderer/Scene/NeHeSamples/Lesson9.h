#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson9 final : public ILesson
	{
	public:
		Lesson9();
		~Lesson9() override;

		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;

		void Update( DWORD milliseconds, const bool keys[] ) override;
		const char* GetDescription() const override;

	private:
		int LoadGLTextures();

	private:

		bool	twinkle;			// Twinkling Stars
		bool	tp;					// 'T' Key Pressed?

		const static int num = 50;				// Number Of Stars To Draw

		typedef struct				// Create A Structure For Star
		{
			int r, g, b;			// Stars Color
			GLfloat dist,			// Stars Distance From Center
				angle;			// Stars Current Angle
		}
		stars;
		stars star[num];			// Need To Keep Track Of 'num' Stars

		GLfloat	zoom = -15.0f;		// Distance Away From Stars
		GLfloat tilt = 90.0f;			// Tilt The View
		GLfloat	spin;				// Spin Stars

		GLuint	loop;				// General Loop Variable
		GLuint	texture[1];			// Storage For One textures

	};
}