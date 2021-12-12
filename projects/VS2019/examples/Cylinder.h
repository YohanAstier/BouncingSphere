#ifndef _CYLINDER_H_
#define _CYLINDER_H_

#include "raylib.h"
#include <raymath.h>
#include "rlgl.h"
#include <math.h>
#include <float.h>
#include <vector>
#include "../projects/VS2019/examples/Sphere.h"
#include "../projects/VS2019/examples/Disk.h"
#define EPSILON 1.e-6f
struct Cylinder
{
	Vector3 pt1;
	Vector3 pt2;
	float radius;
};

struct Cylindrical {
	float rho;
	float theta;
	float y;

	inline Cylindrical operator+(Cylindrical a) {
		return { a.rho + rho,a.theta + theta,a.y + y };
	}
};

Cylindrical CartesianToCylindrical(Vector3 cart);
Vector3 CylindricalToCartesian(Cylindrical cyl);
void MyDrawCylinder(Quaternion q, Cylinder cyl, int nSegmentsTheta, bool drawCaps, Color color);
void MyDrawCylinderPortion(Quaternion q, Cylinder cyl, float startTheta, float endTheta, int nSegmentsTheta, bool drawCaps, Color color);
void MyDrawCylinderWire(Quaternion q, Cylinder cyl, int nSegmentsTheta, bool drawCaps, Color color);
void MyDrawCylinderWiresPortion(Quaternion q, Cylinder cyl, float startTheta, float endTheta, int nSegmentsTheta, bool drawCaps, Color color);
bool isPointOnSeg(Segment s, Vector3 p);
bool InterSegmentInfiniteCylinder(Segment seg, Cylinder cyl, Vector3* interPt, Vector3* interNormal);
bool InterSegmentCylinder(Segment seg, Cylinder cyl, Vector3* interPt, Vector3* interNormal);
bool InterSegmentCapCylinder(Segment seg, Cylinder cyl, Vector3* interPt, Vector3* interNormal);
#endif


