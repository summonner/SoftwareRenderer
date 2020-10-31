#include "framework.h"
#include "Lesson37.h"

namespace NeHe
{
	Lesson37::Lesson37()
	{
	}

	Lesson37::~Lesson37()
	{
	}

	// File Functions
	BOOL Lesson37::ReadMesh()												// Reads The Contents Of The "model.txt" File ( NEW )
	{
		FILE* In = fopen( "Data\\model.txt", "rb" );					// Open The File ( NEW )

		if ( !In )
			return FALSE;											// Return FALSE If File Not Opened ( NEW )

		fread( &polyNum, sizeof( int ), 1, In );						// Read The Header (i.e. Number Of Polygons) ( NEW )

		polyData = new POLYGON[polyNum];							// Allocate The Memory ( NEW )
#pragma warning ( disable : 6029 )
		fread( &polyData[0], sizeof( POLYGON ) * polyNum, 1, In );	// Read In All Polygon Data ( NEW )
#pragma warning ( default : 6029 )
		fclose( In );												// Close The File ( NEW )

		return TRUE;												// It Worked ( NEW )
	}

	// Math Functions
	void Lesson37::Normalize( VECTOR& V )										// Creates A Vector With A Unit Length Of 1 ( NEW )
	{
		float M = Magnitude( V );									// Calculate The Length Of The Vector  ( NEW )

		if ( M != 0.0f )												// Make Sure We Don't Divide By 0  ( NEW )
		{
			V.X /= M;												// Normalize The 3 Components  ( NEW )
			V.Y /= M;
			V.Z /= M;
		}
	}

	void Lesson37::RotateVector( MATRIX& M, VECTOR& V, VECTOR& D )				// Rotate A Vector Using The Supplied Matrix ( NEW )
	{
		D.X = (M.Data[0] * V.X) + (M.Data[4] * V.Y) + (M.Data[8] * V.Z);	// Rotate Around The X Axis ( NEW )
		D.Y = (M.Data[1] * V.X) + (M.Data[5] * V.Y) + (M.Data[9] * V.Z);	// Rotate Around The Y Axis ( NEW )
		D.Z = (M.Data[2] * V.X) + (M.Data[6] * V.Y) + (M.Data[10] * V.Z);	// Rotate Around The Z Axis ( NEW )
	}

	// Engine Functions
	int Lesson37::InitGL( GLvoid )					// Any GL Init Code & User Initialiazation Goes Here
	{
		int i;														// Looping Variable ( NEW )
		char Line[255];												// Storage For 255 Characters ( NEW )
		float shaderData[32][3];									// Storate For The 96 Shader Values ( NEW )

		FILE* In = NULL;											// File Pointer ( NEW )

		// Start Of User Initialization
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );			// Realy Nice perspective calculations

		glClearColor( 0.7f, 0.7f, 0.7f, 0.0f );						// Light Grey Background
		glClearDepth( 1.0f );										// Depth Buffer Setup

		glEnable( GL_DEPTH_TEST );									// Enable Depth Testing
		glDepthFunc( GL_LESS );										// The Type Of Depth Test To Do

		glShadeModel( GL_SMOOTH );									// Enables Smooth Color Shading ( NEW )
		glDisable( GL_LINE_SMOOTH );									// Initially Disable Line Smoothing ( NEW )

		glEnable( GL_CULL_FACE );									// Enable OpenGL Face Culling ( NEW )

		glDisable( GL_LIGHTING );									// Disable OpenGL Lighting ( NEW )

		In = fopen( "Data\\shader.txt", "r" );						// Open The Shader File ( NEW )

		if ( In )														// Check To See If The File Opened ( NEW )
		{
			for ( i = 0; i < 32; i++ )								// Loop Though The 32 Greyscale Values ( NEW )
			{
				if ( feof( In ) )										// Check For The End Of The File ( NEW )
					break;

				fgets( Line, 255, In );								// Get The Current Line ( NEW )

				shaderData[i][0] = shaderData[i][1] = shaderData[i][2] = float( atof( Line ) ); // Copy Over The Value ( NEW )
			}

			fclose( In );											// Close The File ( NEW )
		}

		else
			return FALSE;											// It Went Horribly Horribly Wrong ( NEW )

		glGenTextures( 1, &shaderTexture[0] );						// Get A Free Texture ID ( NEW )

		glBindTexture( GL_TEXTURE_1D, shaderTexture[0] );			// Bind This Texture. From Now On It Will Be 1D ( NEW )

		// For Crying Out Loud Don't Let OpenGL Use Bi/Trilinear Filtering! ( NEW )
		glTexParameteri( GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

		glTexImage1D( GL_TEXTURE_1D, 0, GL_RGB, 32, 0, GL_RGB, GL_FLOAT, shaderData );	// Upload ( NEW )

		lightAngle.X = 0.0f;										// Set The X Direction ( NEW )
		lightAngle.Y = 0.0f;										// Set The Y Direction ( NEW )
		lightAngle.Z = 1.0f;										// Set The Z Direction ( NEW )

		Normalize( lightAngle );										// Normalize The Light Direction ( NEW )

		return ReadMesh();											// Return The Value Of ReadMesh ( NEW )
	}

	int Lesson37::CleanGL( GLvoid ) 										// Any User DeInitialization Goes Here
	{
		glDeleteTextures( 1, &shaderTexture[0] );					// Delete The Shader Texture ( NEW )

		delete[] polyData;											// Delete The Polygon Data ( NEW )
		return TRUE;
	}

	const char* Lesson37::GetDescription() const
	{
		return "Space - Toggle Rotation\n\
				1 - Toggle Outline\n\
				2 - Toggle Anti-Aliasing\n\
				Up/Down - Change Line Width";
	}

	void Lesson37::Update( DWORD milliseconds, bool keys[] )								// Perform Motion Updates Here
	{
		if ( keys[' '] == TRUE )							// Is the Space Bar Being Pressed? ( NEW )
		{
			modelRotate = !modelRotate;								// Toggle Model Rotation On/Off ( NEW )

			keys[' '] = FALSE;
		}

		if ( keys['1'] == TRUE )							// Is The Number 1 Being Pressed? ( NEW )
		{
			outlineDraw = !outlineDraw;								// Toggle Outline Drawing On/Off ( NEW )

			keys['1'] = FALSE;
		}

		if ( keys['2'] == TRUE )							// Is The Number 2 Being Pressed? ( NEW )
		{
			outlineSmooth = !outlineSmooth;							// Toggle Anti-Aliasing On/Off ( NEW )

			keys['2'] = FALSE;
		}

		if ( keys[VK_UP] == TRUE )						// Is The Up Arrow Being Pressed? ( NEW )
		{
			outlineWidth++;											// Increase Line Width ( NEW )

			keys[VK_UP] = FALSE;
		}

		if ( keys[VK_DOWN] == TRUE )						// Is The Down Arrow Being Pressed? ( NEW )
		{
			outlineWidth--;											// Decrease Line Width ( NEW )

			keys[VK_DOWN] = FALSE;
		}

		if ( modelRotate )											// Check To See If Rotation Is Enabled ( NEW )
			modelAngle += (float)(milliseconds) / 10.0f;			// Update Angle Based On The Clock
	}

	int Lesson37::DrawGLScene( GLvoid )
	{
		int i, j;													// Looping Variables ( NEW )

		float TmpShade;												// Temporary Shader Value ( NEW )

		MATRIX TmpMatrix;											// Temporary MATRIX Structure ( NEW )
		VECTOR TmpVector, TmpNormal;								// Temporary VECTOR Structures ( NEW )

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );		// Clear The Buffers
		glLoadIdentity();											// Reset The Matrix

		if ( outlineSmooth )											// Check To See If We Want Anti-Aliased Lines ( NEW )
		{
			glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );				// Use The Good Calculations ( NEW )
			glEnable( GL_LINE_SMOOTH );								// Enable Anti-Aliasing ( NEW )
		}

		else														// We Don't Want Smooth Lines ( NEW )
			glDisable( GL_LINE_SMOOTH );								// Disable Anti-Aliasing ( NEW )

		glTranslatef( 0.0f, 0.0f, -2.0f );							// Move 2 Units Away From The Screen ( NEW )
		glRotatef( modelAngle, 0.0f, 1.0f, 0.0f );					// Rotate The Model On It's Y-Axis ( NEW )

		glGetFloatv( GL_MODELVIEW_MATRIX, TmpMatrix.Data );			// Get The Generated Matrix ( NEW )

		// Cel-Shading Code //
		glEnable( GL_TEXTURE_1D );									// Enable 1D Texturing ( NEW )
		glBindTexture( GL_TEXTURE_1D, shaderTexture[0] );			// Bind Our Texture ( NEW )

		glColor3f( 1.0f, 1.0f, 1.0f );								// Set The Color Of The Model ( NEW )

		glBegin( GL_TRIANGLES );										// Tell OpenGL That We're Drawing Triangles

		for ( i = 0; i < polyNum; i++ )							// Loop Through Each Polygon ( NEW )
		{
			for ( j = 0; j < 3; j++ )								// Loop Through Each Vertex ( NEW )
			{
				TmpNormal.X = polyData[i].Verts[j].Nor.X;		// Fill Up The TmpNormal Structure With
				TmpNormal.Y = polyData[i].Verts[j].Nor.Y;		// The Current Vertices' Normal Values ( NEW )
				TmpNormal.Z = polyData[i].Verts[j].Nor.Z;

				RotateVector( TmpMatrix, TmpNormal, TmpVector );	// Rotate This By The Matrix ( NEW )

				Normalize( TmpVector );							// Normalize The New Normal ( NEW )

				TmpShade = DotProduct( TmpVector, lightAngle );	// Calculate The Shade Value ( NEW )

				if ( TmpShade < 0.0f )
					TmpShade = 0.0f;							// Clamp The Value to 0 If Negative ( NEW )

				glTexCoord1f( TmpShade );						// Set The Texture Co-ordinate As The Shade Value ( NEW )
				glVertex3fv( &polyData[i].Verts[j].Pos.X );		// Send The Vertex Position ( NEW )
			}
		}

		glEnd();													// Tell OpenGL To Finish Drawing

		glDisable( GL_TEXTURE_1D );									// Disable 1D Textures ( NEW )

		// Outline Code //
		if ( outlineDraw )											// Check To See If We Want To Draw The Outline ( NEW )
		{
			glEnable( GL_BLEND );									// Enable Blending ( NEW )
			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );		// Set The Blend Mode ( NEW )

			glPolygonMode( GL_BACK, GL_LINE );						// Draw Backfacing Polygons As Wireframes ( NEW )
			glLineWidth( outlineWidth );								// Set The Line Width ( NEW )

			glCullFace( GL_FRONT );									// Don't Draw Any Front-Facing Polygons ( NEW )

			glDepthFunc( GL_LEQUAL );								// Change The Depth Mode ( NEW )

			glColor3fv( &outlineColor[0] );							// Set The Outline Color ( NEW )

			glBegin( GL_TRIANGLES );									// Tell OpenGL What We Want To Draw

			for ( i = 0; i < polyNum; i++ )						// Loop Through Each Polygon ( NEW )
			{
				for ( j = 0; j < 3; j++ )							// Loop Through Each Vertex ( NEW )
				{
					glVertex3fv( &polyData[i].Verts[j].Pos.X );	// Send The Vertex Position ( NEW )
				}
			}

			glEnd();												// Tell OpenGL We've Finished

			glDepthFunc( GL_LESS );									// Reset The Depth-Testing Mode ( NEW )

			glCullFace( GL_BACK );									// Reset The Face To Be Culled ( NEW )

			glPolygonMode( GL_BACK, GL_FILL );						// Reset Back-Facing Polygon Drawing Mode ( NEW )

			glDisable( GL_BLEND );									// Disable Blending ( NEW )
		}
		return TRUE;
	}
}