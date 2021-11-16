#ifndef _PLANE_H_
#define _PLANE_H_

#include "raylib.h"
#include <raymath.h>
#include "rlgl.h"
#include <math.h>
#include <float.h>
#include <vector>
#include "../projects/VS2019/examples/Sphere.h"
#include "../projects/VS2019/examples/Cylinder.h"

struct Plane {
	Vector3 normal;
	float d;
};

bool InterSegPlane(Segment s, Plane p, Vector3* interPt, Vector3* interNormalPt);
#endif