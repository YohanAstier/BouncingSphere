#include "Ball.h"
Ball initBall(Vector3 pos, float radius) {
	Sphere s = { pos, radius };
	Ball b = { s, .005f, {0,-9.81,0} }; //Tombe par déffaut à cause de la gravité
	return b;
}

Ball moveBall(Ball b) {
	Vector3 dep = Vector3Scale(b.dir, b.speed);
	Ball result = b;
	result.s.pos = Vector3Add(result.s.pos, dep);
	return result;
}

Vector3 nextPos(Ball b) {
	Vector3 dep = Vector3Scale(b.dir, b.speed);
	return Vector3Add(b.s.pos, dep);

}