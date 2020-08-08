#pragma once
#include "ILesson.h"

#define LESSON Lesson18

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
		int CleanGL( GLvoid ) override;

	private:
		int LoadGLTextures();
		void glDrawCube();

	private:
		int		part1;				// Start Of Disc ( NEW )
		int		part2;				// End Of Disc ( NEW )
		int		p1 = 0;				// Increase 1 ( NEW )
		int		p2 = 1;				// Increase 2 ( NEW )

		GLfloat	xrot;				// X Rotation
		GLfloat	yrot;				// Y Rotation
		GLfloat xspeed;				// X Rotation Speed
		GLfloat yspeed;				// Y Rotation Speed
		GLfloat	z = -5.0f;			// Depth Into The Screen

		GLUquadricObj* quadratic;	// Storage For Our Quadratic Objects ( NEW )

		GLfloat LightAmbient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
		GLfloat LightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat LightPosition[4] = { 0.0f, 0.0f, 2.0f, 1.0f };

		GLuint	filter;				// Which Filter To Use
		GLuint	texture[3];			// Storage For 3 Textures
		GLuint  object = 0;			// Which Object To Draw (NEW)
	};
}