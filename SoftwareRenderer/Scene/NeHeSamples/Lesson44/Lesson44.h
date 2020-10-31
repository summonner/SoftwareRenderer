#pragma once
#include "../ILesson.h"
#include "glFont.h"													// Header for fonts
#include "glCamera.h"												// Header for the camera class


namespace NeHe
{
	class Lesson44 final : public ILesson
	{
	public:
		Lesson44();
		~Lesson44() override;

		int InitGL( GLvoid ) override;
		int CleanGL( GLvoid ) override;
		int DrawGLScene( GLvoid ) override;
		const char* GetDescription() const override;
		void Update( DWORD milliseconds, bool keys[] ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;

	private:
		void DrawGLInfo( void );
		bool LoadTexture( LPCSTR szFileName, GLuint& texid );

	private:
		bool		infoOn = FALSE;
		int			gFrames = 0;
		DWORD		gStartTime{};
		DWORD		gCurrentTime{};
		GLfloat		gFPS{};
		glFont		gFont{};
		glCamera	gCamera{};

		GLUquadricObj* qobj{};			//the quadric for our cylinder
		GLint						cylList{};

	};
}