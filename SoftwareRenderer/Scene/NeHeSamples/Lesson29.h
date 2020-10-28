#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson29 final : public ILesson
	{
	private:
		typedef struct
		{
			int width;													// Width Of Image In Pixels
			int height;													// Height Of Image In Pixels
			int format;													// Number Of Bytes Per Pixel
			unsigned char* data;										// Texture Data
		} TEXTURE_IMAGE;

		typedef TEXTURE_IMAGE* P_TEXTURE_IMAGE;							// A Pointer To The Texture Image Data Type


	public:
		Lesson29();
		~Lesson29() override;

		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		//int CleanGL( GLvoid ) override;
		//void Update( DWORD milliseconds, bool keys[] ) override;
		//const char* GetDescription() const override;

	private:
		P_TEXTURE_IMAGE AllocateTextureBuffer( GLint w, GLint h, GLint f );
		void DeallocateTexture( P_TEXTURE_IMAGE t );
		int ReadTextureData( const char* filename, P_TEXTURE_IMAGE buffer );
		void BuildTexture( P_TEXTURE_IMAGE tex );
		void Blit( P_TEXTURE_IMAGE src, P_TEXTURE_IMAGE dst, int src_xstart, int src_ystart, int src_width, int src_height,
			int dst_xstart, int dst_ystart, int blend, int alpha );

	private:
		GLfloat		xrot;												// X Rotation
		GLfloat		yrot;												// Y Rotation
		GLfloat		zrot;												// Z Rotation

		GLuint		texture[1];											// Storage For 1 Texture

		P_TEXTURE_IMAGE t1;												// Pointer To The Texture Image Data Type
		P_TEXTURE_IMAGE t2;												// Pointer To The Texture Image Data Type

	};
}