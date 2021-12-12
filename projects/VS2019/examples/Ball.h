#ifndef _BALL_H
#define _BALL_H
#include <math.h>
#include <float.h>
#include <vector>
#include "Sphere.h"
struct Ball{
	Sphere s;
	double speed;
	Vector3 dir;
};

Ball initBall(Vector3 pos, float radius);
Ball moveBall(Ball b);
Vector3 nextPos(Ball b);

#endif


