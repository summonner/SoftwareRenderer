#pragma once
#include "ILesson.h"
#include "Scene/IMouseInputListener.h"

namespace NeHe
{
	class Lesson32 final : public ILesson, public IMouseInputListener
	{
	private:
		struct TextureImage												// Create A Structure
		{
			GLubyte* imageData{};											// Image Data (Up To 32 Bits)
			GLuint	bpp{};												// Image Color Depth In Bits Per Pixel.
			GLuint	width{};												// Image Width
			GLuint	height{};												// Image Height
			GLuint	texID{};												// Texture ID Used To Select A Texture
		};													// Structure Name

		struct objects
		{
			GLuint	rot{};												// Rotation (0-None, 1-Clockwise, 2-Counter Clockwise)
			bool	hit{};												// Object Hit?
			GLuint	frame{};												// Current Explosion Frame
			GLuint	dir{};												// Object Direction (0-Left, 1-Right, 2-Up, 3-Down)
			GLuint	texid{};												// Object Texture ID
			GLfloat	x{};													// Object X Position
			GLfloat y{};													// Object Y Position
			GLfloat	spin{};												// Object Spin
			GLfloat	distance{};											// Object Distance
		};

	public:
		Lesson32();
		~Lesson32() override;

		int CleanGL( GLvoid ) override;
		int DrawGLScene( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		int InitGL( GLvoid ) override;
		void Update( DWORD milliseconds, bool keys[] ) override;

		void OnMove( int x, int y ) override;
		void OnButton( UINT message ) override;

	private:
		void DrawTargets();												// Declaration
		bool LoadTGA( TextureImage* texture, const char* filename );
		GLvoid BuildFont( GLvoid );
		GLvoid glPrint( GLint x, GLint y, const char* string, ... );
		static int Compare( objects* elem1, objects* elem2 );
		GLvoid InitObject( int num );
		void Selection( void );
		void Object( float width, float height, GLuint texid );
		void Explosion( int num );

	private:
		// User Defined Variables
		GLuint		base{};												// Font Display List
		GLfloat		roll{};												// Rolling Clouds
		GLint		level = 1;											// Current Level
		GLint		miss{};												// Missed Targets
		GLint		kills{};												// Level Kill Counter
		GLint		score{};												// Current Score
		bool		game{};												// Game Over?

		typedef int (*compfn)(const void*, const void*);				// Typedef For Our Compare Function

		TextureImage textures[10];										// Storage For 10 Textures

		objects	object[30];												// Storage For 30 Objects

		struct dimensions
		{												// Object Dimensions
			GLfloat	w{};													// Object Width
			GLfloat h{};													// Object Height
		};

		// Size Of Each Object: Blueface,     Bucket,      Target,       Coke,         Vase
		dimensions size[5] = { {1.0f,1.0f}, {1.0f,1.0f}, {1.0f,1.0f}, {0.5f,1.0f}, {0.75f,1.5f} };
		int	mouse_x{}, mouse_y{};
		RECT window;
	};
}