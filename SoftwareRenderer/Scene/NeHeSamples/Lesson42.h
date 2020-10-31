#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson42 final : public ILesson
	{
	private:

	public:
		Lesson42();
		~Lesson42() override;

		int InitGL( GLvoid ) override;
		int CleanGL( GLvoid ) override;
		int DrawGLScene( GLvoid ) override;
		const char* GetDescription() const override;
		void Update( DWORD milliseconds, bool keys[] ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;

	private:
		void UpdateTex( int dmx, int dmy );
		void Reset( void );

	private:
		// User Defined Variables
		int	mx{}, my{};																// General Loops (Used For Seeking)

		const	int width = 128;													// Maze Width  (Must Be A Power Of 2)
		const	int height = 128;													// Maze Height (Must Be A Power Of 2)

		BOOL	done{};															// Flag To Let Us Know When It's Done
		BOOL	sp{};																// Spacebar Pressed?

		BYTE	r[4]{ 0, }, g[4]{ 0, }, b[4]{ 0, };												// Random Colors (4 Red, 4 Green, 4 Blue)
		BYTE* tex_data{};														// Holds Our Texture Data

		GLfloat	xrot{}, yrot{}, zrot{};												// Use For Rotation Of Objects

		GLUquadricObj* quadric{};													// The Quadric Object
		RECT	rect{};
	};
}