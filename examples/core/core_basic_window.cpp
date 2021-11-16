﻿/*******************************************************************************************
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

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

int main(int argc, char* argv[])
{
	// Initialization
	//--------------------------------------------------------------------------------------
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
	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.f;
	camera.type = CAMERA_PERSPECTIVE;
	SetCameraMode(camera, CAMERA_CUSTOM);  // Set an orbital camera mode

	//TEST CONVERSION CARTESIAN->CYLINDRICAL
	Vector3 pos = { 1,1,1 };
	Cylindrical cyl = CartesianToCylindrical(pos);
	printf("cyl = (%f,%f,%f) ", cyl.rho, cyl.theta, cyl.y);
	cyl = cyl + cyl;
	printf("cyl = (%f,%f,%f) ", cyl.rho, cyl.theta, cyl.y);

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		float deltaTime = GetFrameTime();
		float time = (float)GetTime();

		MyUpdateOrbitalCamera(&camera, deltaTime);

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode3D(camera);
		{
			//

			//3D REFERENTIAL
			HideCursor();
			
			DrawGrid(20, 1.0f);        // Draw a grid
			DrawLine3D({ 0 }, { 0,10,0 }, DARKGRAY);
			DrawSphere({ 10,0,0 }, .2f, RED);
			DrawSphere({ 0,0,10 }, .2f, BLUE);
			DrawSphere({ 0,10,0 }, .2f, GREEN);

			
			//MyDrawDisk({ 0,0,0,0 }, { 0,0,0 }, 5, 20, BLUE)
			Quaternion qOrient = QuaternionFromAxisAngle(Vector3Normalize({ time * 10,time * 100,time * 1000 }), time);
			Sphere sph = { {0,0,0 }, 3 };
			MyDrawSphereWiresPortion(QuaternionIdentity(), sph, 4, 20, 4, 28, 28, 28, PURPLE);

			Cylinder cylinder = { {0,0,0}, {0,2,0}, 2.f };
			//MyDrawCylinderWire(QuaternionIdentity(), cylinder, 28, true, RED);
			//MyDrawCylinderPortion(qOrient, cylinder, 4, 25, 28, true, RED);
			

			//MyDrawSphereWires({ 0,0,0 }, 2, 20, 20, BLUE);

			//MyDrawDiskWire(qOrient, { 0,1,0 }, 5, 20, BLUE);
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
