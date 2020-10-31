#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson38 final : public ILesson
	{
	private:
		struct object													// Create A Structure Called Object
		{
			int   tex;													// Integer Used To Select Our Texture
			float x;													// X Position
			float y;													// Y Position
			float z;													// Z Position
			float yi;													// Y Increase Speed (Fall Speed)
			float spinz;												// Z Axis Spin
			float spinzi;												// Z Axis Spin Speed
			float flap;													// Flapping Triangles :)
			float fi;													// Flap Direction (Increase Value)
		};

	public:
		Lesson38();
		~Lesson38() override;

		int CleanGL( GLvoid ) override;
		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		//const char* GetDescription() const override;
		void Update( DWORD milliseconds, bool keys[] ) override;

	private:
		void SetObject( int loop );
		void LoadGLTextures();

	private:
		// User Defined Variables
		GLuint texture[3]{ 0, };												// Storage For 3 Textures


		object obj[50]{ 0, };													// Create 50 Objects Using The Object Structure

	};
}