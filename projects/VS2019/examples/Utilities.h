#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include "raylib.h"
#include <raymath.h>
#include "rlgl.h"
#include <math.h>
#include <float.h>
#include <vector>
struct Referential {
	Vector3 origin;
	Vector3 i;
	Vector3 j;
	Vector3 k;
	Quaternion quat;
};

Vector3 GlobalToLocalVect(Vector3 vectGlobal, Referential localRef);
Vector3 GlobalToLocalPos(Vector3 posGlobal, Referential localRef);
Vector3 LocalToGlobalVect(Vector3 localVect, Referential localRef);
Vector3 LocalToGlobalPos(Vector3 localPos, Referential localRef);
Referential RotateReferential(Referential r, Quaternion q);
Referential changeReferential(Referential ref, Vector3 translation, Quaternion rotation);
#endif // !_UTILITIES_H_
