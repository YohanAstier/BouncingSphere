#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "raylib.h"
#include <raymath.h>
#include "rlgl.h"
#include <math.h>
#include <float.h>
#include <vector>

struct Sphere {
	Vector3 pos;
	float r;
};

struct Spherical {
	float rho;
	float theta;
	float phi;

	inline Spherical operator+(Spherical a) {
		return { a.rho + rho,a.theta + theta,a.phi + phi };
	}

};

struct Segment {
	Vector3 pt1;
	Vector3 pt2;
};


void MyDrawSphereEx2(Quaternion q, Vector3 centerPos, float radius, int nSegmentsTheta, int nSegmentsPhi, Color color);
void MyDrawSphereWiresEx2(Quaternion q, Vector3 centerPos, float radius, int nSegmentsTheta, int nSegmentsPhi, Color color);
void MyDrawSphereWiresPortion(Quaternion q, Sphere sph, float startTheta, float endTheta, float startPhi, float endPhi, int nSegmentsTheta, int nSegmentsPhi, Color color);
Vector3 SphericalToCartesian(Spherical sph);
void MyDrawSpherePortion(Quaternion q, Sphere sph, float startTheta, float endTheta, float startPhi, float endPhi, int nSegmentsTheta, int nSegmentsPhi, Color color);
bool InterSegmentSphere(Segment seg, Sphere s, Vector3* interPt);
void MyDrawSphereEx2(Vector3 centerPos, float radius, int nSegmentsTheta, int nSegmentsPhi, Color color);
void MyDrawSphereWiresEx2(Vector3 centerPos, float radius, int nSegmentsTheta, int nSegmentsPhi, Color color);
void MyDrawSphereTrianglesAndWiresEx(Vector3 centerPos, float radius, int nSegmentsTheta, int nSegmentsPhi, Color trianglesColor, Color wiresColor);
void MyDrawSphereWires(Vector3 centerPos, float radius, int nSegmentsTheta, int nSegmentsPhi, Color wiresColor);
#endif