#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include "raylib.h"
#include <raymath.h>
#include "rlgl.h"
#include <math.h>
#include <float.h>
#include <vector>
struct Referencial {
	Vector3 origin;
	Vector3 i;
	Vector3 j;
	Vector3 k;
	Quaternion quat;
};

Vector3 GlobalToLocalVect(Vector3 vectGlobal, Referencial localRef);
Vector3 GlobalToLocalPos(Vector3 posGlobal, Referencial localRef);
Vector3 LocalToGlobalVect(Vector3 localVect, Referencial localRef);
Vector3 LocalToGlobalPos(Vector3 localPos, Referencial localRef);
Referencial ReferencialByQuarternion(Referencial r, Quaternion q);
#endif // !_UTILITIES_H_
