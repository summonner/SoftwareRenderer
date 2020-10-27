#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson23 final : public ILesson
	{
	public:
		Lesson23();
		~Lesson23() override;

		void Update( DWORD milliseconds, const bool keys[] ) override;
		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		int CleanGL( GLvoid ) override;
		const char* GetDescription() const override;

	private:
		int LoadGLTextures();
		void glDrawCube();

	private:
		bool	light;				// Lighting ON/OFF
		bool	lp;					// L Pressed? 
		bool	fp;					// F Pressed?
		bool    sp;                 // Spacebar Pressed? 

		int		part1;				// Start Of Disc
		int		part2;				// End Of Disc
		int		p1 = 0;				// Increase 1
		int		p2 = 1;				// Increase 2

		GLfloat	xrot;				// X Rotation
		GLfloat	yrot;				// Y Rotation
		GLfloat xspeed;				// X Rotation Speed
		GLfloat yspeed;				// Y Rotation Speed
		GLfloat	z = -10.0f;			// Depth Into The Screen

		GLUquadricObj* quadratic;	// Storage For Our Quadratic Objects

		GLfloat LightAmbient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
		GLfloat LightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat LightPosition[4] = { 0.0f, 0.0f, 2.0f, 1.0f };

		GLuint	filter;				// Which Filter To Use
		GLuint	texture[6];			// Storage For 6 Textures (MODIFIED)
		GLuint  object = 1;			// Which Object To Draw
	};
}