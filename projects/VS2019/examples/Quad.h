#ifndef _QUAD_H_
#define _QUAD_H_
#include "raylib.h"
#include <raymath.h>
#include "rlgl.h"
#include <math.h>
#include <float.h>
#include <vector>
#include "../projects/VS2019/examples/Sphere.h"
#include "../projects/VS2019/examples/Utilities.h"
#include "../projects/VS2019/examples/Plane.h"
#include "Ball.h"

struct Quad {
	Referential r;
	Vector3 extension;
};

typedef struct Box {
	Referential r;
	Vector3 extension;
	Quad faces[6];
} Box;

typedef struct RoundedBox {
	Box b;
	float r;

} RoundedBox;


void MyDrawQuad(Vector3 center, Vector2 size, Color color);
void MyDrawQuadWire(Vector3 center, Vector2 size, Color color);
void MyDrawQuadRotative(Quaternion q, Vector3 center, Vector2 size, Color color);
bool InterSegmentQuad(Segment seg, Quad quad, Vector3* interPt, Vector3* interNormal);
void MyDrawQuadRotative(Quad quad, Color color);
void MyDrawBox(Box box, Color color);
Box CreateBox(Referential r, Vector3 extension);
RoundedBox CreateRoundedBox(Referential r, Vector3 extension, float rad);
bool interSegBox(Box b, Segment s, Vector3* interPt, Vector3* interNorm);
bool interSegRoundedBox(RoundedBox rb, Segment s, Vector3* interPt, Vector3* interNorm);
bool interDeplacementSphereRoundedBox(Segment s, Ball b, RoundedBox rb, Vector3* interPt, Vector3* interNorm);

#endif
