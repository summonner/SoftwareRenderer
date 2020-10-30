#pragma once
#include "ILesson.h"
#include "Scene/IMouseInputListener.h"

namespace NeHe
{
	class Lesson34 final : public ILesson, public IMouseInputListener
	{
	public:
		Lesson34();
		~Lesson34() override;

		int DrawGLScene( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		int InitGL( GLvoid ) override;
		void Update( DWORD milliseconds, bool keys[] ) override;
		const char* GetDescription() const override;

		void OnMove( int x, int y ) override;
		void OnLButton( bool isPressed ) override;

	private:
		void LoadRawFile( LPCSTR strName, int nSize, BYTE* pHeightMap );
		void RenderHeightMap( BYTE pHeightMap[] );

	private:
#define		MAP_SIZE	  1024							// Size Of Our .RAW Height Map (NEW)
#define		STEP_SIZE	  16							// Width And Height Of Each Quad (NEW)
#define		HEIGHT_RATIO  1.5f							// Ratio That The Y Is Scaled According To The X And Z (NEW)

		bool		bRender = TRUE;								// Polygon Flag Set To TRUE By Default (NEW)
		BYTE g_HeightMap[MAP_SIZE * MAP_SIZE];					// Holds The Height Map Data (NEW)

		float scaleValue = 0.15f;								// Scale Value For The Terrain (NEW)
	};
}