#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson45 final : public ILesson
	{
	public:
		Lesson45();
		~Lesson45() override;

		int CleanGL( GLvoid ) override;
		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		void Update( DWORD milliseconds, const bool keys[] ) override;
	};
}