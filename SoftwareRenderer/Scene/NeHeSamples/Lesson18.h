#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson18 final : public ILesson
	{
	public:
		Lesson18();
		~Lesson18() override;

		void Update( DWORD milliseconds, const bool keys[] ) override;
		const char* GetDescription() const override;

		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		int CleanGL( GLvoid ) override;

	private:
		int LoadGLTextures();
		void glDrawCube();

	private:
		bool	light;				// Lighting ON/OFF
		bool	lp;					// L Pressed? 
		bool	fp;					// F Pressed? 
		bool    sp;                 // Spacebar Pressed? ( NEW )

		int		part1;				// Start Of Disc ( NEW )
		int		part2;				// End Of Disc ( NEW )
		int		p1 = 0;				// Increase 1 ( NEW )
		int		p2 = 1;				// Increase 2 ( NEW )

		GLfloat	xrot;				// X Rotation
		GLfloat	yrot;				// Y Rotation
		GLfloat xspeed;				// X Rotation Speed
		GLfloat yspeed;				// Y Rotation Speed
		GLfloat	z = -5.0f;			// Depth Into The Screen

		GLUquadricObj* quadratic;	// Storage For Our Quadratic Objects ( NEW )

		GLfloat LightAmbient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
		GLfloat LightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat LightPosition[4] = { 0.0f, 0.0f, 2.0f, 1.0f };

		GLuint	filter;				// Which Filter To Use
		GLuint	texture[3];			// Storage For 3 Textures
		GLuint  object;			// Which Object To Draw (NEW)
	};
}