#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson26 final : public ILesson
	{
	public:
		Lesson26();
		~Lesson26() override;

		void Update( DWORD milliseconds, const bool keys[] ) override;
		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		int CleanGL( GLvoid ) override;
		const char* GetDescription() const override;

	private:
		int LoadGLTextures();
		void DrawObject();
		void DrawFloor();

	private:
		// Light Parameters
		GLfloat LightAmb[4] = { 0.7f, 0.7f, 0.7f, 1.0f };	// Ambient Light
		GLfloat LightDif[4] = { 1.0f, 1.0f, 1.0f, 1.0f };	// Diffuse Light
		GLfloat LightPos[4] = { 4.0f, 4.0f, 6.0f, 1.0f };	// Light Position

		GLUquadricObj* q = nullptr;										// Quadratic For Drawing A Sphere

		GLfloat		xrot = 0.0f;						// X Rotation
		GLfloat		yrot = 0.0f;						// Y Rotation
		GLfloat		xrotspeed = 0.0f;						// X Rotation Speed
		GLfloat		yrotspeed = 0.0f;						// Y Rotation Speed
		GLfloat		zoom = -7.0f;						// Depth Into The Screen
		GLfloat		height = 2.0f;						// Height Of Ball From Floor

		GLuint		texture[3] = { 0, };								// 3 Textures
	};
}