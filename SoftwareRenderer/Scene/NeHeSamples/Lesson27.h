#pragma once
#include "ILesson.h"
#include "3dobject.h"									// Header File For 3D Object Handling

namespace NeHe
{
	class Lesson27 final : public ILesson
	{
	private:
		typedef float GLvector4f[4];							// Typedef's For VMatMult Procedure
		typedef float GLmatrix16f[16];							// Typedef's For VMatMult Procedure

	public:
		Lesson27();
		~Lesson27() override;

		void Update( DWORD milliseconds, const bool keys[] ) override;
		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		//int CleanGL( GLvoid ) override;
		const char* GetDescription() const override;

	private:
		void VMatMult( GLmatrix16f M, GLvector4f v );
		int InitGLObjects();
		void DrawGLRoom();

	private:
		glObject	obj;										// Object
		GLfloat		xrot = 0, xspeed = 0;							// X Rotation & X Speed
		GLfloat		yrot = 0, yspeed = 0;							// Y Rotation & Y Speed

		float LightPos[4] = { 0.0f, 5.0f,-4.0f, 1.0f };			// Light Position
		float LightAmb[4] = { 0.2f, 0.2f, 0.2f, 1.0f };			// Ambient Light Values
		float LightDif[4] = { 0.6f, 0.6f, 0.6f, 1.0f };			// Diffuse Light Values
		float LightSpc[4] = { -0.2f, -0.2f, -0.2f, 1.0f };			// Specular Light Values

		float MatAmb[4] = { 0.4f, 0.4f, 0.4f, 1.0f };				// Material - Ambient Values
		float MatDif[4] = { 0.2f, 0.6f, 0.9f, 1.0f };				// Material - Diffuse Values
		float MatSpc[4] = { 0.0f, 0.0f, 0.0f, 1.0f };				// Material - Specular Values
		float MatShn[1] = { 0.0f };								// Material - Shininess

		float ObjPos[3] = { -2.0f,-2.0f,-5.0f };					// Object Position

		GLUquadricObj* q;										// Quadratic For Drawing A Sphere
		float SpherePos[3] = { -4.0f,-5.0f,-6.0f };


	};
}