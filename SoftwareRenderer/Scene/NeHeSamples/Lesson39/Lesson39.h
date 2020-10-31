#pragma once
#include "../ILesson.h"
#include "Physics1.h"											// Header File For Lesson39 (Physics1)

namespace NeHe
{
	class Lesson39 final : public ILesson
	{
	public:
		Lesson39();
		~Lesson39() override;

		int CleanGL( GLvoid ) override;
		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		//const char* GetDescription() const override;
		void Update( DWORD milliseconds, bool keys[] ) override;

	private:
		int LoadGLTextures();
		GLvoid BuildFont();
		GLvoid KillFont( GLvoid );
		GLvoid glPrint( float x, float y, float z, const char* fmt, ... );

	private:
		/*
		ConstantVelocity is an object from Physics1.h. It is a container for simulating masses.
		Specifically, it creates a mass and sets its velocity as (1, 0, 0) so that the mass
		moves with 1.0f meters / second in the x direction.
		*/
		ConstantVelocity* constantVelocity = new ConstantVelocity();

		/*
		MotionUnderGravitation is an object from Physics1.h. It is a container for simulating masses.
		This object applies gravitation to all masses it contains. This gravitation is set by the
		constructor which is (0.0f, -9.81f, 0.0f) for now (see below). This means a gravitational acceleration
		of 9.81 meter per (second * second) in the negative y direction. MotionUnderGravitation
		creates one mass by default and sets its position to (-10, 0, 0) and its velocity to
		(10, 15, 0)
		*/
		MotionUnderGravitation* motionUnderGravitation =
			new MotionUnderGravitation( Vector3D( 0.0f, -9.81f, 0.0f ) );

		/*
		MassConnectedWithSpring is an object from Physics1.h. It is a container for simulating masses.
		This object has a member called connectionPos, which is the connection position of the spring
		it simulates. All masses in this container are pulled towards the connectionPos by a spring
		with a constant of stiffness. This constant is set by the constructor and for now it is 2.0
		(see below).
		*/
		MassConnectedWithSpring* massConnectedWithSpring =
			new MassConnectedWithSpring( 2.0f );

		float slowMotionRatio = 10.0f;									// slowMotionRatio Is A Value To Slow Down The Simulation, Relative To Real World Time
		float timeElapsed = 0;											// Elapsed Time In The Simulation (Not Equal To Real World's Time Unless slowMotionRatio Is 1

		GLuint	base{};													// Base Display List For The Font Set
	};
}