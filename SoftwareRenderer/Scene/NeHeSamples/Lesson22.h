#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson22 final : public ILesson
	{
	public:
		Lesson22();
		~Lesson22() override;

		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;

		void Update( DWORD milliseconds, const bool keys[] ) override;
		//const char* GetDescription() const override;

	private:
		bool isInString( char* string, const char* search );
		bool initMultitexture( void );
		void initLights( void );
		int LoadGLTextures();
		void doCube( void );
		void VMatMult( GLfloat* M, GLfloat* v );
		void SetUpBumps( GLfloat* n, GLfloat* c, GLfloat* l, GLfloat* s, GLfloat* t );
		void doLogo( void );
		bool doMesh1TexelUnits( void );
		bool doMesh2TexelUnits( void );
		bool doMeshNoBumps( void );

	private:
		bool	ep, mp, bp, fp;
		bool	active = true;												// Window Active Flag Set To TRUE By Default
		bool	fullscreen = true;											// Fullscreen Flag Set To Fullscreen Mode By Default
		bool	emboss = false;												// Emboss Only, No Basetexture?
		bool    bumps = true;													// Do Bumpmapping?

		GLfloat	xrot;														// X Rotation
		GLfloat	yrot;														// Y Rotation
		GLfloat xspeed;														// X Rotation Speed
		GLfloat yspeed;														// Y Rotation Speed
		GLfloat	z = -5.0f;													// Depth Into The Screen

		GLuint	filter = 1;													// Which Filter To Use
		GLuint	texture[3];													// Storage For 3 Textures
		GLuint  bump[3];													// Our Bumpmappings
		GLuint  invbump[3];													// Inverted Bumpmaps
		GLuint	glLogo;														// Handle For OpenGL-Logo
		GLuint  multiLogo;													// Handle For Multitexture-Enabled-Logo

		GLfloat LightAmbient[4] = { 0.2f, 0.2f, 0.2f };						// Ambient Light is 20% white
		GLfloat LightDiffuse[4] = { 1.0f, 1.0f, 1.0f };						// Diffuse Light is white
		GLfloat LightPosition[4] = { 0.0f, 0.0f, 2.0f };						// Position is somewhat in front of screen

		GLfloat Gray[4] = { 0.5f,0.5f,0.5f,1.0f };

		// Data Contains The Faces For The Cube In Format 2xTexCoord, 3xVertex;
		// Note That The Tesselation Of The Cube Is Only Absolute Minimum.
		GLfloat data[120] = {
			// FRONT FACE
			0.0f, 0.0f,		-1.0f, -1.0f, +1.0f,
			1.0f, 0.0f,		+1.0f, -1.0f, +1.0f,
			1.0f, 1.0f,		+1.0f, +1.0f, +1.0f,
			0.0f, 1.0f,		-1.0f, +1.0f, +1.0f,
			// BACK FACE
			1.0f, 0.0f,		-1.0f, -1.0f, -1.0f,
			1.0f, 1.0f,		-1.0f, +1.0f, -1.0f,
			0.0f, 1.0f,		+1.0f, +1.0f, -1.0f,
			0.0f, 0.0f,		+1.0f, -1.0f, -1.0f,
			// Top Face
			0.0f, 1.0f,		-1.0f, +1.0f, -1.0f,
			0.0f, 0.0f,		-1.0f, +1.0f, +1.0f,
			1.0f, 0.0f,		+1.0f, +1.0f, +1.0f,
			1.0f, 1.0f,		+1.0f, +1.0f, -1.0f,
			// Bottom Face
			1.0f, 1.0f,		-1.0f, -1.0f, -1.0f,
			0.0f, 1.0f,		+1.0f, -1.0f, -1.0f,
			0.0f, 0.0f,		+1.0f, -1.0f, +1.0f,
			1.0f, 0.0f,		-1.0f, -1.0f, +1.0f,
			// Right Face
			1.0f, 0.0f,		+1.0f, -1.0f, -1.0f,
			1.0f, 1.0f,		+1.0f, +1.0f, -1.0f,
			0.0f, 1.0f,		+1.0f, +1.0f, +1.0f,
			0.0f, 0.0f,		+1.0f, -1.0f, +1.0f,
			// Left Face
			0.0f, 0.0f,		-1.0f, -1.0f, -1.0f,
			1.0f, 0.0f,		-1.0f, -1.0f,  1.0f,
			1.0f, 1.0f,		-1.0f,  1.0f,  1.0f,
			0.0f, 1.0f,		-1.0f,  1.0f, -1.0f
		};

		bool multitextureSupported = false;									// Flag Indicating Whether Multitexturing Is Supported
		bool useMultitexture = true;											// Use It If It Is Supported?
		GLint maxTexelUnits = 1;												// Number Of Texel-Pipelines. This Is At Least 1.

	};
}