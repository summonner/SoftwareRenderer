#pragma once
#include "../ILesson.h"
#include "tvector.h"
#undef bool

namespace NeHe
{
	class Lesson30 final : public ILesson
	{
	private:
		//Plane structure
		struct Plane
		{
			TVector _Position;
			TVector _Normal;
		};
		//Cylinder structure
		struct Cylinder
		{
			TVector _Position;
			TVector _Axis;
			double _Radius{ 0.0 };
		};
		//Explosion structure
		struct Explosion
		{
			TVector _Position;
			float   _Alpha{ 0.0f };
			float   _Scale{ 0.0f };
		};

	public:
		Lesson30();
		~Lesson30() override;

		int DrawGLScene( GLvoid ) override;
		int InitGL( GLvoid ) override;
		GLvoid ReSizeGLScene( GLsizei width, GLsizei height ) override;
		//int CleanGL( GLvoid ) override;
		void Update( DWORD milliseconds, bool keys[] ) override;
		const char* GetDescription() const override;

	private:
		int FindBallCol( TVector& point, double& TimePoint, double Time2, int& BallNr1, int& BallNr2 );
		//Perform Intersection tests with primitives
		int TestIntersionPlane( const Plane& plane, const TVector& position, const TVector& direction, double& lamda, TVector& pNormal );
		int TestIntersionCylinder( const Cylinder& cylinder, const TVector& position, const TVector& direction, double& lamda, TVector& pNormal, TVector& newposition );
		void LoadGLTextures();                    //Loads Texture Objects
		void InitVars();
		void idle();

	private:
		GLfloat spec[4] = { 1.0, 1.0 ,1.0 ,1.0 };      //sets specular highlight of balls
		GLfloat posl[4] = { 0,400,0,1 };               //position of ligth source
		GLfloat amb[4] = { 0.2f, 0.2f, 0.2f ,1.0f };   //global ambient
		GLfloat amb2[4] = { 0.3f, 0.3f, 0.3f ,1.0f };  //ambient of lightsource

		TVector dir;                     //initial direction of camera
		TVector pos;                  //initial position of camera
		float camera_rotation = 0;                  //holds rotation around the Y axis


		TVector veloc;              //initial velocity of balls
		TVector accel;                 //acceleration ie. gravity of balls

		TVector ArrayVel[10];                     //holds velocity of balls
		TVector ArrayPos[10];                     //position of balls
		TVector OldPos[10];                       //old position of balls
		int NrOfBalls;                            //sets the number of balls
		double Time = 0.6;                          //timestep of simulation
		int hook_toball1 = 0, sounds = 1;             //hook camera on ball, and sound on/off


		Plane pl1, pl2, pl3, pl4, pl5;                //the 5 planes of the room
		Cylinder cyl1, cyl2, cyl3;                  //the 2 cylinders of the room
		GLUquadricObj* cylinder_obj;              //Quadratic object to render the cylinders
		GLuint texture[4], dlist;                 //stores texture objects and display list
		Explosion ExplosionArray[20];             //holds max 20 explosions at once
		
	};
}