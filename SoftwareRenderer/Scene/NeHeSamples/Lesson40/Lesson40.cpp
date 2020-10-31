#include "framework.h"
#include "Lesson40.h"

namespace NeHe
{
	/*
	  class RopeSimulation is derived from class Simulation (see Physics1.h). It simulates a rope with
	  point-like particles binded with springs. The springs have inner friction and normal length. One tip of
	  the rope is stabilized at a point in space called "Vector3D ropeConnectionPos". This point can be
	  moved externally by a method "void setRopeConnectionVel(Vector3D ropeConnectionVel)". RopeSimulation
	  creates air friction and a planer surface (or ground) with a normal in +y direction. RopeSimulation
	  implements the force applied by this surface. In the code, the surface is refered as "ground".
	*/
	Lesson40::Lesson40()
		: ropeSimulation( new RopeSimulation(
			80,						// 80 Particles (Masses)
			0.05f,					// Each Particle Has A Weight Of 50 Grams
			10000.0f,				// springConstant In The Rope
			0.05f,					// Normal Length Of Springs In The Rope
			0.2f,					// Spring Inner Friction Constant
			Vector3D( 0, -9.81f, 0 ), // Gravitational Acceleration
			0.02f,					// Air Friction Constant
			100.0f,					// Ground Repel Constant
			0.2f,					// Ground Slide Friction Constant
			2.0f,					// Ground Absoption Constant
			-1.5f ) )					// Height Of Ground
	{
	}

	Lesson40::~Lesson40()
	{
	}

	int Lesson40::InitGL( GLvoid )								// Any GL Init Code & User Initialiazation Goes Here
	{
		ropeSimulation->getMass( ropeSimulation->numOfMasses - 1 )->vel.z = 10.0f;

		glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );									// Black Background
		glClearDepth( 1.0f );													// Depth Buffer Setup
		glShadeModel( GL_SMOOTH );												// Select Smooth Shading
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );						// Set Perspective Calculations To Most Accurate

		return TRUE;															// Return TRUE (Initialization Successful)
	}

	int Lesson40::CleanGL( GLvoid ) 													// Any User DeInitialization Goes Here
	{
		ropeSimulation->release();												// Release The ropeSimulation
		delete(ropeSimulation);													// Delete The ropeSimulation
		ropeSimulation = NULL;
		return TRUE;
	}

	const char* Lesson40::GetDescription() const
	{
		return "Arrows/Home/End - Move";
	}

	void Lesson40::Update( DWORD milliseconds, bool keys[] )											// Perform Motion Updates Here
	{
		Vector3D ropeConnectionVel;												// Create A Temporary Vector3D

		// Keys Are Used To Move The Rope
		if ( keys[VK_RIGHT] == TRUE )									// Is The Right Arrow Being Pressed?
			ropeConnectionVel.x += 3.0f;										// Add Velocity In +X Direction

		if ( keys[VK_LEFT] == TRUE )									// Is The Left Arrow Being Pressed?
			ropeConnectionVel.x -= 3.0f;										// Add Velocity In -X Direction

		if ( keys[VK_UP] == TRUE )									// Is The Up Arrow Being Pressed?
			ropeConnectionVel.z -= 3.0f;										// Add Velocity In +Z Direction

		if ( keys[VK_DOWN] == TRUE )									// Is The Down Arrow Being Pressed?
			ropeConnectionVel.z += 3.0f;										// Add Velocity In -Z Direction

		if ( keys[VK_HOME] == TRUE )									// Is The Home Key Pressed?
			ropeConnectionVel.y += 3.0f;										// Add Velocity In +Y Direction

		if ( keys[VK_END] == TRUE )									// Is The End Key Pressed?
			ropeConnectionVel.y -= 3.0f;										// Add Velocity In -Y Direction

		ropeSimulation->setRopeConnectionVel( ropeConnectionVel );				// Set The Obtained ropeConnectionVel In The Simulation

		float dt = milliseconds / 1000.0f;										// Let's Convert Milliseconds To Seconds

		float maxPossible_dt = 0.002f;											// Maximum Possible dt Is 0.002 Seconds
																				// This Is Needed To Prevent Pass Over Of A Non-Precise dt Value

		int numOfIterations = (int)(dt / maxPossible_dt) + 1;					// Calculate Number Of Iterations To Be Made At This Update Depending On maxPossible_dt And dt
		if ( numOfIterations != 0 )												// Avoid Division By Zero
			dt = dt / numOfIterations;											// dt Should Be Updated According To numOfIterations

		for ( int a = 0; a < numOfIterations; ++a )								// We Need To Iterate Simulations "numOfIterations" Times
			ropeSimulation->operate( dt );
	}

	int Lesson40::DrawGLScene( GLvoid )
	{
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();														// Reset The Modelview Matrix

		// Position Camera 40 Meters Up In Z-Direction.
		// Set The Up Vector In Y-Direction So That +X Directs To Right And +Y Directs To Up On The Window.
		gluLookAt( 0, 0, 4, 0, 0, 0, 0, 1, 0 );

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );					// Clear Screen And Depth Buffer

		// Draw A Plane To Represent The Ground (Different Colors To Create A Fade)
		glBegin( GL_QUADS );
		glColor3ub( 0, 0, 255 );												// Set Color To Light Blue
		glVertex3f( 20, ropeSimulation->groundHeight, 20 );
		glVertex3f( -20, ropeSimulation->groundHeight, 20 );
		glColor3ub( 0, 0, 0 );												// Set Color To Black
		glVertex3f( -20, ropeSimulation->groundHeight, -20 );
		glVertex3f( 20, ropeSimulation->groundHeight, -20 );
		glEnd();

		// Start Drawing Shadow Of The Rope
		glColor3ub( 0, 0, 0 );													// Set Color To Black
		int a;
		for ( a = 0; a < ropeSimulation->numOfMasses - 1; ++a )
		{
			Mass* mass1 = ropeSimulation->getMass( a );
			Vector3D* pos1 = &mass1->pos;

			Mass* mass2 = ropeSimulation->getMass( a + 1 );
			Vector3D* pos2 = &mass2->pos;

			glLineWidth( 2 );
			glBegin( GL_LINES );
			glVertex3f( pos1->x, ropeSimulation->groundHeight, pos1->z );		// Draw Shadow At groundHeight
			glVertex3f( pos2->x, ropeSimulation->groundHeight, pos2->z );		// Draw Shadow At groundHeight
			glEnd();
		}
		// Drawing Shadow Ends Here.

		// Start Drawing The Rope.
		glColor3ub( 255, 255, 0 );												// Set Color To Yellow
		for ( a = 0; a < ropeSimulation->numOfMasses - 1; ++a )
		{
			Mass* mass1 = ropeSimulation->getMass( a );
			Vector3D* pos1 = &mass1->pos;

			Mass* mass2 = ropeSimulation->getMass( a + 1 );
			Vector3D* pos2 = &mass2->pos;

			glLineWidth( 4 );
			glBegin( GL_LINES );
			glVertex3f( pos1->x, pos1->y, pos1->z );
			glVertex3f( pos2->x, pos2->y, pos2->z );
			glEnd();
		}
		// Drawing The Rope Ends Here.

		glFlush();																// Flush The GL Rendering Pipeline
		return TRUE;
	}
}