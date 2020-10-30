#pragma once
#include "../ILesson.h"
#include "Texture.h"
namespace NeHe
{
	class Lesson33 final : public ILesson
	{
	private:
		

	public:
		Lesson33();
		~Lesson33() override;

		int DrawGLScene( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		int InitGL( GLvoid ) override;

	private:
		int LoadGLTextures();

	private:
		float	spin{};													// Spin Variable
		Texture texture[2]{ 0, };												// Storage For 2 Textures ( NEW )
		
	};
}