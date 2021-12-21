#ifndef _BOX_H_
#define _BOX_H_
#include "raylib.h"
#include <raymath.h>
#include "rlgl.h"
#include <math.h>
#include <float.h>
#include <vector>
#include "../projects/VS2019/examples/Sphere.h"
#include "../projects/VS2019/examples/Utilities.h"
#include "../projects/VS2019/examples/Plane.h"
#include "../projects/VS2019/examples/Quad.h"

typedef struct Box {
	Referential r;
	Vector3 extension;
	Quad faces[6];
} Box;

typedef struct RoundedBox {
	Box b;
	float r;
	Cylinder corners[12];
} RoundedBox;


void MyDrawBox(Box box, Color color);
Box CreateBox(Referential r, Vector3 extension);
RoundedBox CreateRoundedBox(Referential r, Vector3 extension, float rad);
bool interSegBox(Box b, Segment s, Vector3* interPt, Vector3* interNorm);
bool interSegRoundedBox(RoundedBox rb, Segment s, Vector3* interPt, Vector3* interNorm);

#endif

