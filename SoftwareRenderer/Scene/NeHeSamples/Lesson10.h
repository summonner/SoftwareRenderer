#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson10 final : public ILesson
	{
	public:
		Lesson10();
		~Lesson10();

		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;

		void Update( DWORD milliseconds, bool keys[] ) override;
		const char* GetDescription() const override;

	private:
		void readstr( FILE* f, char* string );
		void SetupWorld();
		int LoadGLTextures();

	private:
		bool	blend;				// Blending ON/OFF
		bool	bp;					// B Pressed?
		bool	fp;					// F Pressed?

		const float piover180 = 0.0174532925f;
		float heading;
		float xpos;
		float zpos;

		GLfloat	yrot;				// Y Rotation
		GLfloat walkbias = 0;
		GLfloat walkbiasangle = 0;
		GLfloat lookupdown = 0.0f;
		GLfloat	z = 0.0f;				// Depth Into The Screen

		GLuint	filter;				// Which Filter To Use
		GLuint	texture[3];			// Storage For 3 Textures


		typedef struct tagVERTEX
		{
			float x, y, z;
			float u, v;
		} VERTEX;

		typedef struct tagTRIANGLE
		{
			VERTEX vertex[3];
		} TRIANGLE;

		typedef struct tagSECTOR
		{
			int numtriangles;
			TRIANGLE* triangle;
		} SECTOR;

		SECTOR sector1;				// Our Model Goes Here:
	};
}