#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson4 final : public ILesson
	{
	public:
		Lesson4();
		~Lesson4();

		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;

	private:
		GLfloat	rtri;				// Angle For The Triangle ( NEW )
		GLfloat	rquad;				// Angle For The Quad ( NEW )
	};
}