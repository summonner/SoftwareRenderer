#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson19 final : public ILesson
	{
	public:
		Lesson19();
		~Lesson19() override;

		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;

		void Update( DWORD milliseconds, const bool keys[] ) override;
		const char* GetDescription() const override;

	private:
		int LoadGLTextures();

	private:
#define	MAX_PARTICLES	1000		// Number Of Particles To Create

		bool	rainbow = true;				// Rainbow Mode?
		bool	sp;							// Spacebar Pressed?
		bool	rp;							// Enter Key Pressed?

		float	slowdown = 2.0f;				// Slow Down Particles
		float	xspeed;						// Base X Speed (To Allow Keyboard Direction Of Tail)
		float	yspeed;						// Base Y Speed (To Allow Keyboard Direction Of Tail)
		float	zoom = -40.0f;				// Used To Zoom Out

		GLuint	loop;						// Misc Loop Variable
		GLuint	col;						// Current Color Selection
		GLuint	delay;						// Rainbow Effect Delay
		GLuint	texture[1];					// Storage For Our Particle Texture

		typedef struct						// Create A Structure For Particle
		{
			bool	active;					// Active (Yes/No)
			float	life;					// Particle Life
			float	fade;					// Fade Speed
			float	r;						// Red Value
			float	g;						// Green Value
			float	b;						// Blue Value
			float	x;						// X Position
			float	y;						// Y Position
			float	z;						// Z Position
			float	xi;						// X Direction
			float	yi;						// Y Direction
			float	zi;						// Z Direction
			float	xg;						// X Gravity
			float	yg;						// Y Gravity
			float	zg;						// Z Gravity
		}
		particles;							// Particles Structure

		particles particle[MAX_PARTICLES];	// Particle Array (Room For Particle Info)

		static const GLfloat colors[12][3];		// Rainbow Of Colors
		const bool* keys;
	};
}