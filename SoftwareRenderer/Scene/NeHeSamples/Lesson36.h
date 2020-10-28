#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson36 final : public ILesson
	{
	public:
		Lesson36();
		~Lesson36() override;

		int CleanGL( GLvoid ) override;
		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		void Update( DWORD milliseconds, bool keys[] ) override;

	private:
		GLuint EmptyTexture();
		void ReduceToUnit( float vector[3] );
		void calcNormal( float v[3][3], float out[3] );
		void ProcessHelix();
		void ViewOrtho();
		void ViewPerspective();
		void RenderToTexture();
		void DrawBlur( int times, float inc );

	private:
		// User Defined Variables
		float		angle;												// Used To Rotate The Helix
		float		vertexes[4][3];										// Holds Float Info For 4 Sets Of Vertices
		float		normal[3];											// An Array To Store The Normal Data
		GLuint		BlurTexture;										// An Unsigned Int To Store The Texture Number
	};
}