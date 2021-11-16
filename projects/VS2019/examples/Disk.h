#ifndef _DISK_H_
#define _DISK_H_

#include "raylib.h"
#include <raymath.h>
#include "rlgl.h"
#include <math.h>
#include <float.h>
#include <vector>
#include "../projects/VS2019/examples/Sphere.h"

void MyDrawDiskWire(Quaternion q, Vector3 center, float radius, int nSegmentsTheta, Color color);
void MyDrawDiskPortion(Quaternion q, Vector3 center, float radius, float startTheta, float endTheta, int nSegmentsTheta, Color color);
void MyDrawDisk(Quaternion q, Vector3 center, float radius, int nSegmentsTheta, Color color);
#endif


