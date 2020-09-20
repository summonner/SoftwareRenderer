#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson20 final : public ILesson
	{
	public:
		Lesson20();
		~Lesson20() override;

		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;

		void Update( DWORD milliseconds, const bool keys[] ) override;
		const char* GetDescription() const override;

	private:
		int LoadGLTextures();

	private:
		bool	masking = TRUE;		// Masking On/Off
		bool	mp;					// M Pressed?
		bool	sp;					// Space Pressed?
		bool	scene;				// Which Scene To Draw

		GLuint	texture[5];			// Storage For Our Five Textures
		GLuint	loop;				// Generic Loop Variable

		GLfloat	roll;				// Rolling Texture
	};
}