#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson2 : public ILesson
	{
	public:
		Lesson2();
		~Lesson2();

		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
	};
}