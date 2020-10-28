#include "framework.h"
#include "Lesson30.h"
#include "tmatrix.h"
#include "tray.h"
#include "image.h"

namespace NeHe
{
	Lesson30::Lesson30()
		: dir( 0, 0, -10 )
		, pos( 0, -50, 1000 )
		, veloc( 0.5, -0.1, 0.5 )
		, accel( 0, -0.05, 0 )
		, NrOfBalls( 0 )
		, pl1(), pl2(), pl3(), pl4(), pl5()
		, cyl1(), cyl2(), cyl3()
		, cylinder_obj( 0 )
		, texture{ 0, }
		, dlist( 0 )
	{
		InitVars();
	}

	Lesson30::~Lesson30()
	{
	}

	GLvoid Lesson30::ReSizeGLScene( GLsizei width, GLsizei height )		// Resize And Initialize The GL Window
	{
		if ( height == 0 )										// Prevent A Divide By Zero By
		{
			height = 1;										// Making Height Equal One
		}

		glViewport( 0, 0, width, height );						// Reset The Current Viewport

		glMatrixMode( GL_PROJECTION );						// Select The Projection Matrix
		glLoadIdentity();									// Reset The Projection Matrix

		// Calculate The Aspect Ratio Of The Window
		gluPerspective( 50.0f, (GLfloat)width / (GLfloat)height, 10.f, 1700.0f );

		glMatrixMode( GL_MODELVIEW );							// Select The Modelview Matrix
		glLoadIdentity();									// Reset The Modelview Matrix
	}

	/************************************************************************************/

	int Lesson30::InitGL( GLvoid )										// All Setup For OpenGL Goes Here
	{
		float df = 100.0;

		glClearDepth( 1.0f );									// Depth Buffer Setup
		glEnable( GL_DEPTH_TEST );							// Enables Depth Testing
		glDepthFunc( GL_LEQUAL );								// The Type Of Depth Testing To Do
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );	// Really Nice Perspective Calculations

		glClearColor( 0, 0, 0, 0 );
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

		glShadeModel( GL_SMOOTH );
		glEnable( GL_CULL_FACE );
		glEnable( GL_DEPTH_TEST );


		glMaterialfv( GL_FRONT, GL_SPECULAR, spec );
		glMaterialfv( GL_FRONT, GL_SHININESS, &df );

		glEnable( GL_LIGHTING );
		glLightfv( GL_LIGHT0, GL_POSITION, posl );
		glLightfv( GL_LIGHT0, GL_AMBIENT, amb2 );
		glEnable( GL_LIGHT0 );

		glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb );
		glEnable( GL_COLOR_MATERIAL );
		glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );

		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE );

		glEnable( GL_TEXTURE_2D );
		LoadGLTextures();

		//Construct billboarded explosion primitive as display list
		//4 quads at right angles to each other
		glNewList( dlist = glGenLists( 1 ), GL_COMPILE );
		glBegin( GL_QUADS );
		glRotatef( -45, 0, 1, 0 );
		glNormal3f( 0, 0, 1 );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -50, -40, 0 );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 50, -40, 0 );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 50, 40, 0 );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -50, 40, 0 );
		glNormal3f( 0, 0, -1 );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -50, 40, 0 );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 50, 40, 0 );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 50, -40, 0 );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -50, -40, 0 );

		glNormal3f( 1, 0, 0 );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 0, -40, 50 );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 0, -40, -50 );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 0, 40, -50 );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 0, 40, 50 );
		glNormal3f( -1, 0, 0 );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 0, 40, 50 );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 0, 40, -50 );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 0, -40, -50 );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 0, -40, 50 );
		glEnd();
		glEndList();

		return TRUE;										// Initialization Went OK
	}

	/************************************************************************************/

	int Lesson30::DrawGLScene( GLvoid )	            // Here's Where We Do All The Drawing
	{
		int i;

		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

		//set camera in hookmode 
		if ( hook_toball1 )
		{
			TVector unit_followvector = ArrayVel[0];
			unit_followvector.unit();
			gluLookAt( ArrayPos[0].X() + 250, ArrayPos[0].Y() + 250, ArrayPos[0].Z(), ArrayPos[0].X() + ArrayVel[0].X(), ArrayPos[0].Y() + ArrayVel[0].Y(), ArrayPos[0].Z() + ArrayVel[0].Z(), 0, 1, 0 );

		}
		else
			gluLookAt( pos.X(), pos.Y(), pos.Z(), pos.X() + dir.X(), pos.Y() + dir.Y(), pos.Z() + dir.Z(), 0, 1.0, 0.0 );


		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glRotatef( camera_rotation, 0, 1, 0 );

		//render balls
		for ( i = 0; i < NrOfBalls; i++ )
		{
			switch ( i )
			{
			case 1: glColor3f( 1.0f, 1.0f, 1.0f );
				break;
			case 2: glColor3f( 1.0f, 1.0f, 0.0f );
				break;
			case 3: glColor3f( 0.0f, 1.0f, 1.0f );
				break;
			case 4: glColor3f( 0.0f, 1.0f, 0.0f );
				break;
			case 5: glColor3f( 0.0f, 0.0f, 1.0f );
				break;
			case 6: glColor3f( 0.65f, 0.2f, 0.3f );
				break;
			case 7: glColor3f( 1.0f, 0.0f, 1.0f );
				break;
			case 8: glColor3f( 0.0f, 0.7f, 0.4f );
				break;
			default: glColor3f( 1.0f, 0, 0 );
			}
			glPushMatrix();
			glTranslated( ArrayPos[i].X(), ArrayPos[i].Y(), ArrayPos[i].Z() );
			gluSphere( cylinder_obj, 20, 20, 20 );
			glPopMatrix();
		}


		glEnable( GL_TEXTURE_2D );

		//render walls(planes) with texture
		glBindTexture( GL_TEXTURE_2D, texture[3] );
		glColor3f( 1, 1, 1 );
		glBegin( GL_QUADS );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 320, 320, 320 );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 320, -320, 320 );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -320, -320, 320 );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -320, 320, 320 );

		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -320, 320, -320 );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -320, -320, -320 );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 320, -320, -320 );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 320, 320, -320 );

		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 320, 320, -320 );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 320, -320, -320 );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 320, -320, 320 );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 320, 320, 320 );

		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -320, 320, 320 );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -320, -320, 320 );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -320, -320, -320 );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -320, 320, -320 );
		glEnd();

		//render floor (plane) with colours
		glBindTexture( GL_TEXTURE_2D, texture[2] );
		glBegin( GL_QUADS );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -320, -320, 320 );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 320, -320, 320 );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 320, -320, -320 );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -320, -320, -320 );
		glEnd();

		//render columns(cylinders)
		glBindTexture( GL_TEXTURE_2D, texture[0] );   /* choose the texture to use.*/
		glColor3f( 0.5, 0.5, 0.5 );
		glPushMatrix();
		glRotatef( 90, 1, 0, 0 );
		glTranslatef( 0, 0, -500 );
		gluCylinder( cylinder_obj, 60, 60, 1000, 20, 2 );
		glPopMatrix();

		glPushMatrix();
		glTranslatef( 200, -300, -500 );
		gluCylinder( cylinder_obj, 60, 60, 1000, 20, 2 );
		glPopMatrix();

		glPushMatrix();
		glTranslatef( -200, 0, 0 );
		glRotatef( 135, 1, 0, 0 );
		glTranslatef( 0, 0, -500 );
		gluCylinder( cylinder_obj, 30, 30, 1000, 20, 2 );
		glPopMatrix();

		//render/blend explosions
		glEnable( GL_BLEND );
		glDepthMask( GL_FALSE );
		glBindTexture( GL_TEXTURE_2D, texture[1] );
		for ( i = 0; i < 20; i++ )
		{
			if ( ExplosionArray[i]._Alpha >= 0 )
			{
				glPushMatrix();
				ExplosionArray[i]._Alpha -= 0.01f;
				ExplosionArray[i]._Scale += 0.03f;
				glColor4f( 1, 1, 0, ExplosionArray[i]._Alpha );
				glScalef( ExplosionArray[i]._Scale, ExplosionArray[i]._Scale, ExplosionArray[i]._Scale );
				glTranslatef( (float)ExplosionArray[i]._Position.X() / ExplosionArray[i]._Scale, (float)ExplosionArray[i]._Position.Y() / ExplosionArray[i]._Scale, (float)ExplosionArray[i]._Position.Z() / ExplosionArray[i]._Scale );
				glCallList( dlist );
				glPopMatrix();
			}
		}
		glDepthMask( GL_TRUE );
		glDisable( GL_BLEND );
		glDisable( GL_TEXTURE_2D );


		return TRUE;										// Keep Going
	}


	/*************************************************************************************/
	/*************************************************************************************/
	/***                  Find if any of the current balls                            ****/
	/***             intersect with each other in the current timestep                ****/
	/***Returns the index of the 2 itersecting balls, the point and time of intersection */
	/*************************************************************************************/
	/*************************************************************************************/
	int Lesson30::FindBallCol( TVector& point, double& TimePoint, double Time2, int& BallNr1, int& BallNr2 )
	{
		TVector RelativeV;
		TRay rays;
		double MyTime = 0.0, Add = Time2 / 150.0, Timedummy = 10000, Timedummy2 = -1;
		TVector posi;

		//Test all balls against eachother in 150 small steps
		for ( int i = 0; i < NrOfBalls - 1; i++ )
		{
			for ( int j = i + 1; j < NrOfBalls; j++ )
			{
				RelativeV = ArrayVel[i] - ArrayVel[j];
				rays = TRay( OldPos[i], TVector::unit( RelativeV ) );
				MyTime = 0.0;

				if ( (rays.dist( OldPos[j] )) > 40 ) continue;

				while ( MyTime < Time2 )
				{
					MyTime += Add;
					posi = OldPos[i] + RelativeV * MyTime;
					if ( posi.dist( OldPos[j] ) <= 40 )
					{
						point = posi;
						if ( Timedummy > ( MyTime - Add ) ) Timedummy = MyTime - Add;
						BallNr1 = i;
						BallNr2 = j;
						break;
					}

				}
			}

		}

		if ( Timedummy != 10000 )
		{
			TimePoint = Timedummy;
			return 1;
		}

		return 0;
	}

	/*************************************************************************************/
	/*************************************************************************************/
	/***             Main loop of the simulation                                      ****/
	/***      Moves, finds the collisions and responses of the objects in the         ****/
	/***      current time step.                                                      ****/
	/*************************************************************************************/
	/*************************************************************************************/
	void Lesson30::idle()
	{
		double rt, rt2, rt4, lamda = 10000;
		TVector norm, uveloc;
		TVector normal, point, time;
		double RestTime, BallTime;
		TVector Pos2;
		int BallNr = 0, dummy = 0, BallColNr1, BallColNr2;
		TVector Nc;

		if ( !hook_toball1 )
		{
			camera_rotation += 0.1f;
			if ( camera_rotation > 360 )
				camera_rotation = 0;
		}

		RestTime = Time;
		lamda = 1000;

		//Compute velocity for next timestep using Euler equations
		int j;
		for ( j = 0; j < NrOfBalls; j++ )
			ArrayVel[j] += accel * RestTime;

		//While timestep not over
		while ( RestTime > ZERO )
		{
			lamda = 10000;   //initialize to very large value

			//For all the balls find closest intersection between balls and planes/cylinders
			for ( int i = 0; i < NrOfBalls; i++ )
			{
				//compute new position and distance
				OldPos[i] = ArrayPos[i];
				TVector::unit( ArrayVel[i], uveloc );
				ArrayPos[i] = ArrayPos[i] + ArrayVel[i] * RestTime;
				rt2 = OldPos[i].dist( ArrayPos[i] );

				//Test if collision occured between ball and all 5 planes
				if ( TestIntersionPlane( pl1, OldPos[i], uveloc, rt, norm ) )
				{
					//Find intersection time
					rt4 = rt * RestTime / rt2;

					//if smaller than the one already stored replace and in timestep
					if ( rt4 <= lamda )
					{
						if ( rt4 <= RestTime + ZERO )
							if ( !((rt <= ZERO) && (uveloc.dot( norm ) > ZERO)) )
							{
								normal = norm;
								point = OldPos[i] + uveloc * rt;
								lamda = rt4;
								BallNr = i;
							}
					}
				}

				if ( TestIntersionPlane( pl2, OldPos[i], uveloc, rt, norm ) )
				{
					rt4 = rt * RestTime / rt2;

					if ( rt4 <= lamda )
					{
						if ( rt4 <= RestTime + ZERO )
							if ( !((rt <= ZERO) && (uveloc.dot( norm ) > ZERO)) )
							{
								normal = norm;
								point = OldPos[i] + uveloc * rt;
								lamda = rt4;
								BallNr = i;
								dummy = 1;
							}
					}

				}

				if ( TestIntersionPlane( pl3, OldPos[i], uveloc, rt, norm ) )
				{
					rt4 = rt * RestTime / rt2;

					if ( rt4 <= lamda )
					{
						if ( rt4 <= RestTime + ZERO )
							if ( !((rt <= ZERO) && (uveloc.dot( norm ) > ZERO)) )
							{
								normal = norm;
								point = OldPos[i] + uveloc * rt;
								lamda = rt4;
								BallNr = i;
							}
					}
				}

				if ( TestIntersionPlane( pl4, OldPos[i], uveloc, rt, norm ) )
				{
					rt4 = rt * RestTime / rt2;

					if ( rt4 <= lamda )
					{
						if ( rt4 <= RestTime + ZERO )
							if ( !((rt <= ZERO) && (uveloc.dot( norm ) > ZERO)) )
							{
								normal = norm;
								point = OldPos[i] + uveloc * rt;
								lamda = rt4;
								BallNr = i;
							}
					}
				}

				if ( TestIntersionPlane( pl5, OldPos[i], uveloc, rt, norm ) )
				{
					rt4 = rt * RestTime / rt2;

					if ( rt4 <= lamda )
					{
						if ( rt4 <= RestTime + ZERO )
							if ( !((rt <= ZERO) && (uveloc.dot( norm ) > ZERO)) )
							{
								normal = norm;
								point = OldPos[i] + uveloc * rt;
								lamda = rt4;
								BallNr = i;
							}
					}
				}

				//Now test intersection with the 3 cylinders
				if ( TestIntersionCylinder( cyl1, OldPos[i], uveloc, rt, norm, Nc ) )
				{
					rt4 = rt * RestTime / rt2;

					if ( rt4 <= lamda )
					{
						if ( rt4 <= RestTime + ZERO )
							if ( !((rt <= ZERO) && (uveloc.dot( norm ) > ZERO)) )
							{
								normal = norm;
								point = Nc;
								lamda = rt4;
								BallNr = i;
							}
					}

				}
				if ( TestIntersionCylinder( cyl2, OldPos[i], uveloc, rt, norm, Nc ) )
				{
					rt4 = rt * RestTime / rt2;

					if ( rt4 <= lamda )
					{
						if ( rt4 <= RestTime + ZERO )
							if ( !((rt <= ZERO) && (uveloc.dot( norm ) > ZERO)) )
							{
								normal = norm;
								point = Nc;
								lamda = rt4;
								BallNr = i;
							}
					}

				}
				if ( TestIntersionCylinder( cyl3, OldPos[i], uveloc, rt, norm, Nc ) )
				{
					rt4 = rt * RestTime / rt2;

					if ( rt4 <= lamda )
					{
						if ( rt4 <= RestTime + ZERO )
							if ( !((rt <= ZERO) && (uveloc.dot( norm ) > ZERO)) )
							{
								normal = norm;
								point = Nc;
								lamda = rt4;
								BallNr = i;
							}
					}

				}
			}

			//After all balls were teste with planes/cylinders test for collision
			//between them and replace if collision time smaller
			if ( FindBallCol( Pos2, BallTime, RestTime, BallColNr1, BallColNr2 ) )
			{
				if ( sounds )
					PlaySound( _T("Data/Explode.wav"), NULL, SND_FILENAME | SND_ASYNC );

				if ( (lamda == 10000) || (lamda > BallTime) )
				{
					RestTime = RestTime - BallTime;

					TVector pb1, pb2, xaxis, U1x, U1y, U2x, U2y, V1x, V1y, V2x, V2y;
					double a, b;

					pb1 = OldPos[BallColNr1] + ArrayVel[BallColNr1] * BallTime;
					pb2 = OldPos[BallColNr2] + ArrayVel[BallColNr2] * BallTime;
					xaxis = (pb2 - pb1).unit();

					a = xaxis.dot( ArrayVel[BallColNr1] );
					U1x = xaxis * a;
					U1y = ArrayVel[BallColNr1] - U1x;

					xaxis = (pb1 - pb2).unit();
					b = xaxis.dot( ArrayVel[BallColNr2] );
					U2x = xaxis * b;
					U2y = ArrayVel[BallColNr2] - U2x;

					V1x = (U1x + U2x - (U1x - U2x)) * 0.5;
					V2x = (U1x + U2x - (U2x - U1x)) * 0.5;
					V1y = U1y;
					V2y = U2y;

					for ( j = 0; j < NrOfBalls; j++ )
						ArrayPos[j] = OldPos[j] + ArrayVel[j] * BallTime;

					ArrayVel[BallColNr1] = V1x + V1y;
					ArrayVel[BallColNr2] = V2x + V2y;

					//Update explosion array
					for ( j = 0; j < 20; j++ )
					{
						if ( ExplosionArray[j]._Alpha <= 0 )
						{
							ExplosionArray[j]._Alpha = 1;
							ExplosionArray[j]._Position = ArrayPos[BallColNr1];
							ExplosionArray[j]._Scale = 1;
							break;
						}
					}

					continue;
				}
			}




			//End of tests 
			//If test occured move simulation for the correct timestep
			//and compute response for the colliding ball
			if ( lamda != 10000 )
			{
				RestTime -= lamda;

				for ( j = 0; j < NrOfBalls; j++ )
					ArrayPos[j] = OldPos[j] + ArrayVel[j] * lamda;

				rt2 = ArrayVel[BallNr].mag();
				ArrayVel[BallNr].unit();
				ArrayVel[BallNr] = TVector::unit( (normal * (2 * normal.dot( -ArrayVel[BallNr] ))) + ArrayVel[BallNr] );
				ArrayVel[BallNr] = ArrayVel[BallNr] * rt2;

				//Update explosion array
				for ( j = 0; j < 20; j++ )
				{
					if ( ExplosionArray[j]._Alpha <= 0 )
					{
						ExplosionArray[j]._Alpha = 1;
						ExplosionArray[j]._Position = point;
						ExplosionArray[j]._Scale = 1;
						break;
					}
				}
			}
			else RestTime = 0;

		}

	}

	/*************************************************************************************/
	/*************************************************************************************/
	/***        Init Variables                                                        ****/
	/*************************************************************************************/
	/*************************************************************************************/
	void Lesson30::InitVars()
	{
		//create palnes
		pl1._Position = TVector( 0, -300, 0 );
		pl1._Normal = TVector( 0, 1, 0 );
		pl2._Position = TVector( 300, 0, 0 );
		pl2._Normal = TVector( -1, 0, 0 );
		pl3._Position = TVector( -300, 0, 0 );
		pl3._Normal = TVector( 1, 0, 0 );
		pl4._Position = TVector( 0, 0, 300 );
		pl4._Normal = TVector( 0, 0, -1 );
		pl5._Position = TVector( 0, 0, -300 );
		pl5._Normal = TVector( 0, 0, 1 );


		//create cylinders
		cyl1._Position = TVector( 0, 0, 0 );
		cyl1._Axis = TVector( 0, 1, 0 );
		cyl1._Radius = 60.0 + 20.0;
		cyl2._Position = TVector( 200, -300, 0 );
		cyl2._Axis = TVector( 0, 0, 1 );
		cyl2._Radius = 60.0 + 20.0;
		cyl3._Position = TVector( -200, 0, 0 );
		cyl3._Axis = TVector( 0, 1, 1 );
		cyl3._Axis.unit();
		cyl3._Radius = 30.0 + 20.0;
		//create quadratic object to render cylinders
		cylinder_obj = gluNewQuadric();
		gluQuadricTexture( cylinder_obj, GL_TRUE );

		//Set initial positions and velocities of balls
		//also initialize array which holds explosions
		NrOfBalls = 10;
		ArrayVel[0] = veloc;
		ArrayPos[0] = TVector( 199, 180, 10 );
		ExplosionArray[0]._Alpha = 0;
		ExplosionArray[0]._Scale = 1;
		ArrayVel[1] = veloc;
		ArrayPos[1] = TVector( 0, 150, 100 );
		ExplosionArray[1]._Alpha = 0;
		ExplosionArray[1]._Scale = 1;
		ArrayVel[2] = veloc;
		ArrayPos[2] = TVector( -100, 180, -100 );
		ExplosionArray[2]._Alpha = 0;
		ExplosionArray[2]._Scale = 1;
		int i;
		for ( i = 3; i < 10; i++ )
		{
			ArrayVel[i] = veloc;
			ArrayPos[i] = TVector( -500 + i * 75.0, 300, -500 + i * 50.0 );
			ExplosionArray[i]._Alpha = 0;
			ExplosionArray[i]._Scale = 1;
		}
		for ( i = 10; i < 20; i++ )
		{
			ExplosionArray[i]._Alpha = 0;
			ExplosionArray[i]._Scale = 1;
		}
	}

	/*************************************************************************************/
	/*************************************************************************************/
	/***        Fast Intersection Function between ray/plane                          ****/
	/*************************************************************************************/
	/*************************************************************************************/
	int Lesson30::TestIntersionPlane( const Plane& plane, const TVector& position, const TVector& direction, double& lamda, TVector& pNormal )
	{

		double DotProduct = direction.dot( plane._Normal );
		double l2;

		//determine if ray paralle to plane
		if ( (DotProduct < ZERO) && (DotProduct > -ZERO) )
			return 0;

		l2 = (plane._Normal.dot( plane._Position - position )) / DotProduct;

		if ( l2 < -ZERO )
			return 0;

		pNormal = plane._Normal;
		lamda = l2;
		return 1;

	}

	/*************************************************************************************/
	/*************************************************************************************/
	/***        Fast Intersection Function between ray/cylinder                       ****/
	/*************************************************************************************/
	int Lesson30::TestIntersionCylinder( const Cylinder& cylinder, const TVector& position, const TVector& direction, double& lamda, TVector& pNormal, TVector& newposition )
	{
		TVector RC;
		double d;
		double t, s;
		TVector n, D, O;
		double ln;
		double in, out;


		TVector::subtract( position, cylinder._Position, RC );
		TVector::cross( direction, cylinder._Axis, n );

		ln = n.mag();

		if ( (ln < ZERO) && (ln > -ZERO) ) return 0;

		n.unit();

		d = fabs( RC.dot( n ) );

		if ( d <= cylinder._Radius )
		{
			TVector::cross( RC, cylinder._Axis, O );
			t = -O.dot( n ) / ln;
			TVector::cross( n, cylinder._Axis, O );
			O.unit();
			s = fabs( sqrt( cylinder._Radius * cylinder._Radius - d * d ) / direction.dot( O ) );

			in = t - s;
			out = t + s;

			if ( in < -ZERO )
			{
				if ( out < -ZERO ) return 0;
				else lamda = out;
			}
			else
				if ( out < -ZERO )
				{
					lamda = in;
				}
				else
					if ( in < out ) lamda = in;
					else lamda = out;

			newposition = position + direction * lamda;
			TVector HB = newposition - cylinder._Position;
			pNormal = HB - cylinder._Axis * (HB.dot( cylinder._Axis ));
			pNormal.unit();

			return 1;
		}

		return 0;
	}

	/*************************************************************************************/
	/*************************************************************************************/
	/***        Load Bitmaps And Convert To Textures                                  ****/
	/*************************************************************************************/
	void Lesson30::LoadGLTextures()
	{
		/* Load Texture*/
		Image* image1, * image2, * image3, * image4;

		/* allocate space for texture*/
		image1 = (Image*)malloc( sizeof( Image ) );
		if ( image1 == NULL )
		{
			printf( "Error allocating space for image" );
			exit( 0 );
		}
		image2 = (Image*)malloc( sizeof( Image ) );
		if ( image2 == NULL )
		{
			printf( "Error allocating space for image" );
			exit( 0 );
		}
		image3 = (Image*)malloc( sizeof( Image ) );
		if ( image3 == NULL )
		{
			printf( "Error allocating space for image" );
			exit( 0 );
		}
		image4 = (Image*)malloc( sizeof( Image ) );
		if ( image4 == NULL )
		{
			printf( "Error allocating space for image" );
			exit( 0 );
		}

		if ( !ImageLoad( "data/marble.bmp", image1 ) )
		{
			exit( 1 );
		}
		if ( !ImageLoad( "data/spark.bmp", image2 ) )
		{
			exit( 1 );
		}
		if ( !ImageLoad( "data/boden.bmp", image3 ) )
		{
			exit( 1 );
		}
		if ( !ImageLoad( "data/wand.bmp", image4 ) )
		{
			exit( 1 );
		}

		/* Create Texture	*****************************************/
		glGenTextures( 2, &texture[0] );
		glBindTexture( GL_TEXTURE_2D, texture[0] );   /* 2d texture (x and y size)*/

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* scale linearly when image bigger than texture*/
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* scale linearly when image smalled than texture*/
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

		/* 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, */
		/* border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.*/
		glTexImage2D( GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data );

		/* Create Texture	******************************************/
		glBindTexture( GL_TEXTURE_2D, texture[1] );   /* 2d texture (x and y size)*/

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* scale linearly when image bigger than texture*/
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* scale linearly when image smalled than texture*/
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

		/* 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, */
		/* border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.*/
		glTexImage2D( GL_TEXTURE_2D, 0, 3, image2->sizeX, image2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image2->data );


		/* Create Texture	********************************************/
		glGenTextures( 2, &texture[2] );
		glBindTexture( GL_TEXTURE_2D, texture[2] );   /* 2d texture (x and y size)*/

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* scale linearly when image bigger than texture*/
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* scale linearly when image smalled than texture*/
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

		/* 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, */
		/* border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.*/
		glTexImage2D( GL_TEXTURE_2D, 0, 3, image3->sizeX, image3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image3->data );

		/* Create Texture	*********************************************/
		glBindTexture( GL_TEXTURE_2D, texture[3] );   /* 2d texture (x and y size)*/

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); /* scale linearly when image bigger than texture*/
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); /* scale linearly when image smalled than texture*/
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

		/* 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, */
		/* border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.*/
		glTexImage2D( GL_TEXTURE_2D, 0, 3, image4->sizeX, image4->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image4->data );

		free( image1->data );
		free( image1 );
		free( image2->data );
		free( image2 );
		free( image3->data );
		free( image3 );
		free( image4->data );
		free( image4 );

	};

	const char* Lesson30::GetDescription() const
	{
		return "Arrows - Move Camera\n\
				+/- - Increase / Decrease Simulation TimeStep\n\
				F2 : Hook Camera to Ball\n\
				F3 : Sound On / Off";
	}

	void Lesson30::Update( DWORD milliseconds, bool keys[] )
	{
		idle();

		if ( keys[VK_UP] )    pos += TVector( 0, 0, -10 );
		if ( keys[VK_UP] )    pos += TVector( 0, 0, 10 );
		if ( keys[VK_LEFT] )  camera_rotation += 10;
		if ( keys[VK_RIGHT] ) camera_rotation -= 10;
		if ( keys[VK_ADD] )
		{
			Time += 0.1;
			keys[VK_ADD] = FALSE;
		}
		if ( keys[VK_SUBTRACT] )
		{
			Time -= 0.1;
			keys[VK_SUBTRACT] = FALSE;
		}
		if ( keys[VK_F3] )
		{
			sounds ^= 1;
			keys[VK_F3] = FALSE;
		}
		if ( keys[VK_F2] )
		{
			hook_toball1 ^= 1;
			camera_rotation = 0;
			keys[VK_F2] = FALSE;
		}
	}
}