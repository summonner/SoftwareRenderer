#pragma once
#include "../ILesson.h"

class Model;
namespace NeHe
{
	class Lesson31 final : public ILesson
	{
	public:
		Lesson31();
		~Lesson31() override;

		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		//int CleanGL( GLvoid ) override;

	public:
		static GLuint LoadGLTexture( const char* filename );

	private:
		Model* pModel = NULL;												// Holds The Model Data
		GLfloat	yrot = 0.0f;													// Y Rotation
	};
}