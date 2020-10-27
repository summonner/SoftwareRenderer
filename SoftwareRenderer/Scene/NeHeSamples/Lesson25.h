#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson25 final : public ILesson
	{
	private:
		typedef struct											// Structure For 3D Points
		{
			float	x, y, z;									// X, Y & Z Points
		} VERTEX;												// Called VERTEX

		typedef struct											// Structure For An Object
		{
			int		verts;										// Number Of Vertices For The Object
			VERTEX* points;									// One Vertice (Vertex x,y & z)
		} OBJECT;												// Called OBJECT

	public:
		Lesson25();
		~Lesson25() override;

		void Update( DWORD milliseconds, const bool keys[] ) override;
		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		int CleanGL( GLvoid ) override;
		const char* GetDescription() const override;

	private:
		void objallocate( OBJECT* k, int n );
		void objfree( OBJECT* k );
		void readstr( FILE* f, char* string );
		void objload( const char* name, OBJECT* k );
		VERTEX calculate( int i );

	private:
		GLfloat		xrot, yrot, zrot,								// X, Y & Z Rotation
					xspeed, yspeed, zspeed,						// X, Y & Z Spin Speed
					cx, cy, cz = -15;								// X, Y & Z Position

		int			key = 1;										// Used To Make Sure Same Morph Key Is Not Pressed
		int			step = 0, steps = 200;							// Step Counter And Maximum Number Of Steps
		bool		morph = FALSE;								// Default morph To False (Not Morphing)

		int			maxver;										// Will Eventually Hold The Maximum Number Of Vertices
		OBJECT		morph1, morph2, morph3, morph4,				// Our 4 Morphable Objects (morph1,2,3 & 4)
					helper, * sour, * dest;							// Helper Object, Source Object, Destination Object

	};
}