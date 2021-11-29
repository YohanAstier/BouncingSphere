#include "Quad.h"

void MyDrawQuad(Vector3 center, Vector2 size, Color color) {
	DrawTriangle3D(center, { center.x + size.x, center.y , center.z + size.y }, { center.x + size.x, center.y, center.z - size.y }, color); //triangle droite
	DrawTriangle3D(center, { center.x + size.x, center.y, center.z - size.y }, { center.x - size.x, center.y, center.z - size.y }, color); //triangle bas
	DrawTriangle3D(center, { center.x - size.x, center.y, center.z - size.y }, { center.x - size.x, center.y, center.z + size.y }, color); //triangle gauche
	DrawTriangle3D(center, { center.x - size.x, center.y, center.z + size.y }, { center.x + size.x, center.y, center.z + size.y }, color); //triangle haut
}

void MyDrawQuadWire(Vector3 center, Vector2 size, Color color) {

	DrawLine3D({ center.x + size.x, center.y, center.z + size.y }, { center.x + size.x, center.y, center.z - size.y }, color);
	DrawLine3D({ center.x + size.x, center.y, center.z - size.y }, { center.x - size.x, center.y, center.z - size.y }, color);
	DrawLine3D({ center.x - size.x, center.y, center.z - size.y }, { center.x - size.x, center.y, center.z + size.y }, color);
	DrawLine3D({ center.x - size.x, center.y, center.z + size.y }, { center.x + size.x, center.y, center.z + size.y }, color);

	DrawLine3D(center, { center.x + size.x, center.y, center.z - size.y }, color);
	DrawLine3D(center, { center.x - size.x, center.y, center.z - size.y }, color);
	DrawLine3D(center, { center.x - size.x, center.y, center.z + size.y }, color);
	DrawLine3D(center, { center.x + size.x, center.y, center.z + size.y }, color);

}



void MyDrawQuadRotative(Quaternion q, Vector3 center, Vector2 size, Color color) {
	rlPushMatrix();

	float angle;
	Vector3 vector;
	QuaternionToAxisAngle(q, &vector, &angle);
	rlRotatef(angle * RAD2DEG, vector.x, vector.y, vector.z);

	rlTranslatef(center.x, center.y, center.z);
	rlScalef(size.x, 0, size.y);




	rlColor4ub(color.r, color.g, color.b, color.a);

	//FACE DESSOUS
	//triangle 1
	rlBegin(RL_TRIANGLES);
	rlVertex3f(0, 0, 0);
	rlVertex3f(-1, 0, -1);
	rlVertex3f(1, 0, -1);

	//triangle 2
	rlVertex3f(1, 0, 1);
	rlVertex3f(0, 0, 0);
	rlVertex3f(1, 0, -1);

	//triangle 3
	rlVertex3f(0, 0, 0);
	rlVertex3f(1, 0, 1);
	rlVertex3f(-1, 0, 1);

	//triangle 4
	rlVertex3f(-1, 0, -1);
	rlVertex3f(0, 0, 0);
	rlVertex3f(-1, 0, 1);

	//FACE DESSUS
	//triangle 1
	rlBegin(RL_TRIANGLES);
	rlVertex3f(-1, 0, -1);
	rlVertex3f(0, 0, 0);
	rlVertex3f(1, 0, -1);

	//triangle 2
	rlVertex3f(0, 0, 0);
	rlVertex3f(1, 0, 1);
	rlVertex3f(1, 0, -1);

	//triangle 3
	rlVertex3f(1, 0, 1);
	rlVertex3f(0, 0, 0);
	rlVertex3f(-1, 0, 1);

	//triangle 4
	rlVertex3f(0, 0, 0);
	rlVertex3f(-1, 0, -1);
	rlVertex3f(-1, 0, 1);

	rlEnd();
	rlPopMatrix();
}

bool InterSegmentQuad(Segment seg, Quad quad, Vector3* interPt, Vector3* interNormal) {
	Plane p;

	p.d = Vector3DotProduct(quad.r.origin, quad.r.j);
	p.normal = quad.r.j;
	if (!InterSegPlane(seg, p, interPt, interNormal)) return false;

	//Verifie si a l'intérieur du carré
	Vector3 localPoint = GlobalToLocalPos(*interPt, quad.r);
	return (0 <= abs(localPoint.x) && abs(localPoint.x) <= quad.r.origin.x + quad.extension.x
		&& 0 <= abs(localPoint.y) && abs(localPoint.y) <= quad.r.origin.y + quad.extension.y
		&& 0 <= abs(localPoint.z) && abs(localPoint.z) <= quad.r.origin.z + quad.extension.z);
}

void MyDrawQuadRotative(Quaternion q, Quad quad, Color color) {
	rlPushMatrix();

	float angle;
	Vector3 vector;
	QuaternionToAxisAngle(q, &vector, &angle);
	rlRotatef(angle * RAD2DEG, vector.x, vector.y, vector.z);

	rlScalef(quad.extension.x, quad.extension.y, quad.extension.z);
	rlTranslatef(quad.r.origin.x, quad.r.origin.y, quad.r.origin.z);


	rlColor4ub(color.r, color.g, color.b, color.a);

	rlBegin(RL_TRIANGLES);

	rlVertex3f(0, 0, 0);
	rlVertex3f(0, 0, 1);
	rlVertex3f(1, 0, 1);

	//triangle 2
	rlVertex3f(0, 0, 0);
	rlVertex3f(1, 0, 1);
	rlVertex3f(0, 0, 1);

	//triangle 3
	rlVertex3f(0, 0, 0);
	rlVertex3f(1, 0, 0);
	rlVertex3f(1, 0, 1);

	//triangle 4
	rlVertex3f(0, 0, 0);
	rlVertex3f(1, 0, 1);
	rlVertex3f(1, 0, 0);


	rlEnd();
	rlPopMatrix();
}