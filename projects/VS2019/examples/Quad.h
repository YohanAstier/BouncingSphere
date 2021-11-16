#ifndef _QUAD_H_
#define _QUAD_H_
#include "raylib.h"
#include <raymath.h>
#include "rlgl.h"
#include <math.h>
#include <float.h>
#include <vector>
#include "../projects/VS2019/examples/Sphere.h"

void MyDrawQuad(Vector3 center, Vector2 size, Color color);
void MyDrawQuadWire(Vector3 center, Vector2 size, Color color);
void MyDrawQuadRotative(Quaternion q, Vector3 center, Vector2 size, Color color);

#endif
