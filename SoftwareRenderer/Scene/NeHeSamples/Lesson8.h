#pragma once
#include "ILesson.h"

#define LESSON Lesson8

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
		GLfloat	xrot;				// X Rotation
		GLfloat	yrot;				// Y Rotation
		GLfloat xspeed;				// X Rotation Speed
		GLfloat yspeed;				// Y Rotation Speed
		GLfloat	z = -5.0f;			// Depth Into The Screen

		GLfloat LightAmbient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
		GLfloat LightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat LightPosition[4] = { 0.0f, 0.0f, 2.0f, 1.0f };

		GLuint	filter;				// Which Filter To Use
		GLuint	texture[3];			// Storage For 3 Textures
	};
}