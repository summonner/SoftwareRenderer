#pragma once
#include "ILesson.h"

namespace NeHe
{
	class Lesson21 final : public ILesson
	{
	public:
		Lesson21();
		~Lesson21() override;

		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		int CleanGL( GLvoid ) override;

		void Update( DWORD milliseconds, const bool keys[] ) override;
		//const char* GetDescription() const override;

	private:
		int LoadGLTextures();
		void TimerInit( void );
		float TimerGetTime();
		void ResetObjects( void );
		GLvoid BuildFont( GLvoid );
		GLvoid KillFont( GLvoid );
		GLvoid glPrint( GLint x, GLint y, int set, const char* fmt, ... );

	private:
		bool	vline[11][10];										// Keeps Track Of Verticle Lines
		bool	hline[10][11];										// Keeps Track Of Horizontal Lines
		bool	ap;													// 'A' Key Pressed?
		bool	filled;												// Done Filling In The Grid?
		bool	gameover;											// Is The Game Over?
		bool	anti = TRUE;											// Antialiasing?
		bool	active = TRUE;										// Window Active Flag Set To TRUE By Default
		bool	fullscreen = TRUE;									// Fullscreen Flag Set To Fullscreen Mode By Default

		int		loop1;												// Generic Loop1
		int		loop2;												// Generic Loop2
		int		delay;												// Enemy Delay
		int		adjust = 3;											// Speed Adjustment For Really Slow Video Cards
		int		lives = 5;											// Player Lives
		int		level = 1;											// Internal Game Level
		int		level2 = level;										// Displayed Game Level
		int		stage = 1;											// Game Stage

		struct	object												// Create A Structure For Our Player
		{
			int		fx, fy;											// Fine Movement Position
			int		x, y;											// Current Player Position
			float	spin;											// Spin Direction
		};

		struct	object player;										// Player Information
		struct	object enemy[9];									// Enemy Information
		struct	object hourglass;									// Hourglass Information

		struct			 											// Create A Structure For The Timer Information
		{
			__int64       frequency;									// Timer Frequency
			float         resolution;									// Timer Resolution
			unsigned long mm_timer_start;								// Multimedia Timer Start Value
			unsigned long mm_timer_elapsed;							// Multimedia Timer Elapsed Time
			bool			performance_timer;							// Using The Performance Timer?
			__int64       performance_timer_start;					// Performance Timer Start Value
			__int64       performance_timer_elapsed;					// Performance Timer Elapsed Time
		} timer;													// Structure Is Named timer

		int		steps[6] = { 1, 2, 4, 5, 10, 20 };					// Stepping Values For Slow Video Adjustment

		GLuint	texture[2];											// Font Texture Storage Space
		GLuint	base;												// Base Display List For The Font
	};
}