#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson16 final : public ILesson
	{
	public:
		Lesson16();
		~Lesson16() override;

		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;

		void Update( DWORD milliseconds, const bool keys[] ) override;
		const char* GetDescription() const override;

	private:
		int LoadGLTextures();

	private:
		bool	light;				// Lighting ON/OFF
		bool	lp;					// L Pressed?
		bool	fp;					// F Pressed?
		bool	gp;					// G Pressed? ( NEW )

		GLfloat	xrot;				// X Rotation
		GLfloat	yrot;				// Y Rotation
		GLfloat xspeed;				// X Rotation Speed
		GLfloat yspeed;				// Y Rotation Speed
		GLfloat	z = -5.0f;			// Depth Into The Screen

		GLfloat LightAmbient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
		GLfloat LightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat LightPosition[4] = { 0.0f, 0.0f, 2.0f, 1.0f };

		GLuint	filter;				// Which Filter To Use
		GLuint	texture[3];			// Storage For 3 Textures

		GLuint	fogMode[3] = { GL_EXP, GL_EXP2, GL_LINEAR };	// Storage For Three Types Of Fog
		GLuint	fogfilter = 0;								// Which Fog Mode To Use 
		GLfloat	fogColor[4] = { 0.5f,0.5f,0.5f,1.0f };		// Fog Color
	};
}