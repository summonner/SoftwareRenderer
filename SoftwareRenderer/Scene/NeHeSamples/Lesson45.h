#pragma once
#include "ILesson.h"

#define LESSON Lesson45

namespace NeHe
{
	class LESSON : public ILesson
	{
	public:
		LESSON();
		~LESSON() override;

		int CleanGL( GLvoid ) override;
		int DrawGLScene( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		int InitGL( GLvoid ) override;
		void Update( DWORD milliseconds, const bool keys[] ) override;
	};
}