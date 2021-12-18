#include "Ball.h"
Ball initBall(Vector3 pos, float radius) {
	Sphere s = { pos, radius };
	Ball b = { s, .05f, {0,0,0} }; //Tombe par déffaut à cause de la gravité
	return b;
}

Segment moveBall(Ball* b) {
	Vector3 dep = Vector3Scale(b->dir, b->speed);
	Segment seg;
	seg.pt1 = b->s.pos;
	b->s.pos = Vector3Add(b->s.pos, dep);
	seg.pt2 = b->s.pos;

	return seg;
}

Vector3 nextPos(Ball b) {
	Vector3 dep = Vector3Scale(b.dir, b.speed);
	return Vector3Add(b.s.pos, dep);

}

void fall(Ball* b, float deltaTime) {
	//accelere la chute
	b->dir = Vector3Subtract(b->dir, { 0, 9.81f * deltaTime, 0 });
}

void boing(Ball* b, Vector3 norm) {
	b->dir = Vector3Reflect(b->dir, norm);
}