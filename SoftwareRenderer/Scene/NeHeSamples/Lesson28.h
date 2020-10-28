#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson28 final : public ILesson
	{
	private:
		typedef struct point_3d
		{			// Structure for a 3-dimensional point (NEW)
			double x, y, z;
		} POINT_3D;

		typedef struct bpatch
		{				// Structure for a 3rd degree bezier patch (NEW)
			POINT_3D	anchors[4][4];			// 4x4 grid of anchor points
			GLuint		dlBPatch;				// Display List for Bezier Patch
			GLuint		texture;				// Texture for the patch
		} BEZIER_PATCH;

	public:
		Lesson28();
		~Lesson28() override;

		void Update( DWORD milliseconds, bool keys[] ) override;
		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		//int CleanGL( GLvoid ) override;
		const char* GetDescription() const override;

	private:
		POINT_3D pointAdd( POINT_3D p, POINT_3D q );
		POINT_3D pointTimes( double c, POINT_3D p );
		POINT_3D makePoint( double a, double b, double c );
		POINT_3D Bernstein( float u, POINT_3D* p );
		GLuint genBezier( BEZIER_PATCH patch, int divs );
		void initBezier( void );
		BOOL LoadGLTexture( GLuint* texPntr, const char* name );

	private:
		GLfloat			rotz = 0.0f;		// Rotation about the Z axis
		BEZIER_PATCH	mybezier;			// The bezier patch we're going to use (NEW)
		BOOL			showCPoints = TRUE;	// Toggles displaying the control point grid (NEW)
		int				divs = 7;			// Number of intrapolations (conrols poly resolution) (NEW)

	};
}