#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson3 final : public ILesson
	{
	public:
		Lesson3();
		~Lesson3();

		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
	};
}