#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson37 final : public ILesson
	{
	private:
		// User Defined Structures
		typedef struct tagMATRIX										// A Structure To Hold An OpenGL Matrix ( NEW )
		{
			float Data[16];												// We Use [16] Due To OpenGL's Matrix Format ( NEW )
		}
		MATRIX;

		typedef struct tagVECTOR										// A Structure To Hold A Single Vector ( NEW )
		{
			float X, Y, Z;												// The Components Of The Vector ( NEW )
		}
		VECTOR;

		typedef struct tagVERTEX										// A Structure To Hold A Single Vertex ( NEW )
		{
			VECTOR Nor;													// Vertex Normal ( NEW )
			VECTOR Pos;													// Vertex Position ( NEW )
		}
		VERTEX;

		typedef struct tagPOLYGON										// A Structure To Hold A Single Polygon ( NEW )
		{
			VERTEX Verts[3];											// Array Of 3 VERTEX Structures ( NEW )
		}
		POLYGON;

	public:
		Lesson37();
		~Lesson37() override;

		int CleanGL( GLvoid ) override;
		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		const char* GetDescription() const override;
		void Update( DWORD milliseconds, bool keys[] ) override;

	private:
		BOOL ReadMesh();

		inline float DotProduct( VECTOR& V1, VECTOR& V2 )				// Calculate The Angle Between The 2 Vectors ( NEW )
		{
			return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;				// Return The Angle ( NEW )
		}

		inline float Magnitude( VECTOR& V )								// Calculate The Length Of The Vector ( NEW )
		{
			return sqrtf( V.X * V.X + V.Y * V.Y + V.Z * V.Z );			// Return The Length Of The Vector ( NEW )
		}

		void Normalize( VECTOR& V );
		void RotateVector( MATRIX& M, VECTOR& V, VECTOR& D );

	private:
		// User Defined Variables
		bool		outlineDraw = true;								// Flag To Draw The Outline ( NEW )
		bool		outlineSmooth = false;							// Flag To Anti-Alias The Lines ( NEW )
		float		outlineColor[3] = { 0.0f, 0.0f, 0.0f };				// Color Of The Lines ( NEW )
		float		outlineWidth = 3.0f;								// Width Of The Lines ( NEW )

		VECTOR		lightAngle{};											// The Direction Of The Light ( NEW )
		bool		lightRotate = false;							// Flag To See If We Rotate The Light ( NEW )

		float		modelAngle = 0.0f;								// Y-Axis Angle Of The Model ( NEW )
		bool        modelRotate = false;							// Flag To Rotate The Model ( NEW )

		POLYGON*	polyData = NULL;								// Polygon Data ( NEW )
		int			polyNum = 0;								// Number Of Polygons ( NEW )

		GLuint		shaderTexture[1]{ 0, };									// Storage For One Texture ( NEW )

	};
}