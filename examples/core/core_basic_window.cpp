/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <raymath.h>
#include "rlgl.h"
#include <math.h>
#include <float.h>
#include <vector>
#include "../projects/VS2019/examples/Sphere.h"
#include "../projects/VS2019/examples/Disk.h"
#include "../projects/VS2019/examples/Cylinder.h"
#include "../projects/VS2019/examples/Quad.h"
#include "../projects/VS2019/examples/Plane.h"
#include "../projects/VS2019/examples/Ball.h"
#include "../../projects/VS2019/examples/Utilities.h"
#include "../../projects/VS2019/examples/Box.h"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

#define RADIUS					.5f

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

int main(int argc, char* argv[])
{
	//-------------- INIT
	//
	float screenSizeCoef = 1.4f;
	const int screenWidth = 1000 * screenSizeCoef;
	const int screenHeight = 820 * screenSizeCoef;

	InitWindow(screenWidth, screenHeight, "Bouncy Sphere");

	SetTargetFPS(60);

	//CAMERA
	Vector3 cameraPos = { 8.0f, 15.0f, 14.0f };
	Camera camera = { 0 };
	camera.position = cameraPos;
	camera.target = { 0.0f, 0.0f, 0.0f };
	camera.up = { 0.0f, 10.0f, 0.0f };
	camera.fovy = 90.f;
	camera.type = CAMERA_PERSPECTIVE;
	SetCameraMode(camera, CAMERA_CUSTOM);  // Set an orbital camera mode

	//init the ball
	Ball b = initBall({ 0,10,0 }, RADIUS);

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{

		float deltaTime = GetFrameTime();
		float time = (float)GetTime();

		MyUpdateOrbitalCamera(&camera, deltaTime);

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode3D(camera);
		{
			HideCursor();
			//------------------- INITIALISATION DU TERRAIN
			std::vector<Box> boxVector;
			// Terrain
			// Sol
			Quaternion quat = QuaternionFromAxisAngle(Vector3Normalize({ 0,0,-1 }), PI / 2);
			Vector3 origin = { 0,0,0 };
			Vector3 extension = { 0.2,10,10 };
			Referential r = { origin,
				{1,0,0},
				{0,1,0},
				{0,0,1}, QuaternionIdentity()};
			Referential rGround = RotateReferential(r, quat);
			Box bGround = CreateBox(rGround, extension);
			MyDrawBox(bGround,LIME);
			boxVector.push_back(bGround);

			// Mur devant
			origin = { 0,5,10+0.2 };
			extension = { 10,5,0.2 };
			Referential rForward = {
				origin,
				{1,0,0},
				{0,1,0},
				{0,0,1}, QuaternionIdentity() 
			};
			Box bForward = CreateBox(rForward, extension);
			MyDrawBox(bForward, LIGHTGRAY);
			boxVector.push_back(bForward);

			// Mur derrière
			origin = { 0,5,-10 - 0.2 };
			extension = { 10,5,0.2 };
			Referential rBehind = {
				origin,
				{1,0,0},
				{0,1,0},
				{0,0,1}, QuaternionIdentity()
			};
			Box bBehind = CreateBox(rBehind, extension);
			MyDrawBox(bBehind, LIGHTGRAY);
			boxVector.push_back(bBehind);

			// Mur gauche
			origin = { -10-0.2, 5, 0 };
			extension = { 0.2,5,10 };
			Referential rLeft = {
				origin,
				{1,0,0},
				{0,1,0},
				{0,0,1}, QuaternionIdentity()
			};
			Box bLeft = CreateBox(rLeft, extension);
			MyDrawBox(bLeft, LIGHTGRAY);
			boxVector.push_back(bLeft);
			// Mur droit
			origin = { 10 + 0.2, 5, 0 };
			extension = { 0.2,5,10 };
			Referential rRight = {
				origin,
				{1,0,0},
				{0,1,0},
				{0,0,1}, QuaternionIdentity()
			};
			Box bRight = CreateBox(rRight, extension);
			MyDrawBox(bRight, LIGHTGRAY);
			boxVector.push_back(bRight);

			//
			//-------------------- INIT BOX TERRAIN
			

			origin = { -0.5, 1, 0 };
			extension = { 1,1,2 };
			Referential r1 = {
				origin,
				{1,0,0},
				{0,1,0},
				{0,0,1}, QuaternionIdentity()
			};
			r1 = RotateReferential(r1, QuaternionFromAxisAngle({ 1,0,1 }, PI / 2));
			Box b1 = CreateBox(r1, extension);

			MyDrawBox(b1, RED);
			boxVector.push_back(b1);


			origin = { -5, 0.5, 2 };
			extension = { 2,0.5,1 };
			Referential r2 = {
				origin,
				{1,0,0},
				{0,1,0},
				{0,0,1}, QuaternionIdentity()
			};
			r2 = RotateReferential(r2, QuaternionFromAxisAngle({ 1,0,-1 }, PI / 2));
			Box b2 = CreateBox(r2, extension);
			MyDrawBox(b2, GOLD);
			boxVector.push_back(b2);


			origin = { -5, 2, -5 };
			extension = { 1,2,3 };
			Referential r3 = {
				origin,
				{1,0,0},
				{0,1,0},
				{0,0,1}, QuaternionIdentity()
			};
			r3 = RotateReferential(r3, QuaternionFromAxisAngle({ 1,0,1 }, PI / 2));
			Box b3 = CreateBox(r3, extension);
			MyDrawBox(b3, PURPLE);
			boxVector.push_back(b3);

			origin = { -5, 1, 8 };
			extension = { 1,1,2 };
			Referential r4 = {
				origin,
				{1,0,0},
				{0,1,0},
				{0,0,1}, QuaternionIdentity()
			};
			r4 = RotateReferential(r4, QuaternionFromAxisAngle({ 1,0,1 }, PI / 2));
			Box b4 = CreateBox(r4, extension);
			MyDrawBox(b4, YELLOW);
			boxVector.push_back(b4);

			origin = { 5, 1, -8 };
			extension = { 2, 1, 1.5};
			Referential r5 = {
				origin,
				{1,0,0},
				{0,1,0},
				{0,0,1}, QuaternionIdentity()
			};
			r5 = RotateReferential(r5, QuaternionFromAxisAngle({ 0,-1,1 }, PI / 2));
			Box b5 = CreateBox(r5, extension);
			MyDrawBox(b5, BLUE);
			boxVector.push_back(b5);

			origin = { 0, 0.5, -6 };
			extension = { 1, 0.5, 2 };
			Referential r6 = {
				origin,
				{1,0,0},
				{0,1,0},
				{0,0,1}, QuaternionIdentity()
			};
			r6 = RotateReferential(r6, QuaternionFromAxisAngle({ -1,0,1 }, PI / 2));
			Box b6 = CreateBox(r6, extension);
			MyDrawBox(b6, DARKBLUE);
			boxVector.push_back(b6);

			origin = { 6, 1, 6 };
			extension = { 1.5, 1, 3 };
			Referential r7 = {
				origin,
				{1,0,0},
				{0,1,0},
				{0,0,1}, QuaternionIdentity()
			};
			r7 = RotateReferential(r7, QuaternionFromAxisAngle({ 1,0,-1 }, PI / 2));
			Box b7 = CreateBox(r7, extension);
			MyDrawBox(b7, DARKBLUE);
			boxVector.push_back(b7);

			origin = { 0, 0.5, 8 };
			extension = { 2, 0.5, 1 };
			Referential r8 = {
				origin,
				{1,0,0},
				{0,1,0},
				{0,0,1}, QuaternionIdentity()
			};
			r8 = RotateReferential(r8, QuaternionFromAxisAngle({ -1,0,1 }, PI / 2));
			Box b8 = CreateBox(r8, extension);
			MyDrawBox(b8, MAROON);
			boxVector.push_back(b8);

			origin = { 5, 0.5, -2 };
			extension = { 2, 0.5, 1 };
			Referential r9 = {
				origin,
				{1,0,0},
				{0,1,0},
				{0,0,1}, QuaternionIdentity()
			};
			r9 = RotateReferential(r9, QuaternionFromAxisAngle({ 1,1,0 }, PI / 2));
			Box b9 = CreateBox(r9, extension);
			MyDrawBox(b9, GREEN);
			boxVector.push_back(b9);
			
			//---------------------------- FIN INIT TERRAIN

			//---------------------------- BALL COLLISION ET MOUVEMENT
			MyDrawSphereEx2(b.s.pos, b.s.r, 24, 24, BLACK);
			fall(&b, GetTime() - time);
			time = GetTime();
			Segment deplacement = moveBall(&b);
			Vector3 interPt;
			Vector3 interNorm;
			int isBoing = 0;
			for each (Box box in boxVector)
			{
				RoundedBox rb = CreateRoundedBox(box.r,box.extension, RADIUS);
					if (interSegRoundedBox(rb,deplacement, &interPt, &interNorm))
					{
						BounceBall(&b, interNorm);
						moveBall(&b);
					}
			}
			
			//---------------------------- FIN BALL COLLISION ET MOUVEMENT
			
			
		}
		EndMode3D();

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------  
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
