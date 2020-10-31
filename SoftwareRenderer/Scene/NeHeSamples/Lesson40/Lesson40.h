#pragma once
#include "../ILesson.h"
#include "Physics2.h"											// Header File For Lesson39 (Physics1)

namespace NeHe
{
	class Lesson40 final : public ILesson
	{
	public:
		Lesson40();
		~Lesson40() override;

		int InitGL( GLvoid ) override;
		int CleanGL( GLvoid ) override;
		int DrawGLScene( GLvoid ) override;
		const char* GetDescription() const override;
		void Update( DWORD milliseconds, bool keys[] ) override;

	private:
		RopeSimulation* ropeSimulation;
	};
}