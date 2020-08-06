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
		int InitGL( GLvoid ) override;
		void Update( DWORD milliseconds );
	};
}