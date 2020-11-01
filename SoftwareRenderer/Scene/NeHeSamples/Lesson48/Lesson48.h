#pragma once
#include "../ILesson.h"
#include "Scene/IMouseInputListener.h"
#include "ArcBall.h"												// NEW: ArcBall Header


namespace NeHe
{
	class Lesson48 final : public ILesson, public IMouseInputListener
	{
	public:
		Lesson48();
		~Lesson48() override;

		int InitGL( GLvoid ) override;
		int CleanGL( GLvoid ) override;
		int DrawGLScene( GLvoid ) override;
		void Update( DWORD milliseconds, bool keys[] ) override;
		const char* GetDescription() const override;

		void OnMove( int x, int y ) override;
		void OnButton( UINT message ) override;

	private:
		void Torus( float MinorRadius, float MajorRadius );

	private:
		// User Defined Variables
		GLUquadricObj* quadratic{};											// Used For Our Quadric

		const float PI2 = 2.0 * 3.1415926535f;								// PI Squared

		Matrix4fT   Transform = { 1.0f,  0.0f,  0.0f,  0.0f,				// NEW: Final Transform
									 0.0f,  1.0f,  0.0f,  0.0f,
									 0.0f,  0.0f,  1.0f,  0.0f,
									 0.0f,  0.0f,  0.0f,  1.0f };

		Matrix3fT   LastRot = { 1.0f,  0.0f,  0.0f,					// NEW: Last Rotation
									 0.0f,  1.0f,  0.0f,
									 0.0f,  0.0f,  1.0f };

		Matrix3fT   ThisRot = { 1.0f,  0.0f,  0.0f,					// NEW: This Rotation
									 0.0f,  1.0f,  0.0f,
									 0.0f,  0.0f,  1.0f };

		ArcBallT    ArcBall{ 640.0f, 480.0f };				                // NEW: ArcBall Instance
		Point2fT    MousePt{};												// NEW: Current Mouse Point
		bool        isClicked = false;										// NEW: Clicking The Mouse?
		bool        isRClicked = false;										// NEW: Clicking The Right Mouse Button?
		bool        isDragging = false;					                    // NEW: Dragging The Mouse?


	};
}