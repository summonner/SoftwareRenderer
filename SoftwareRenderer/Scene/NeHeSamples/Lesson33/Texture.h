#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Scene/gl/glAdapter.h"

typedef	struct									
{
	GLubyte	* imageData;									// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
	GLuint	type;											// Image Type (GL_RGB, GL_RGBA)
} Texture;	

bool LoadTGA( Texture*, const char* );								// Function Prototype For LoadTGA ( NEW )

#endif