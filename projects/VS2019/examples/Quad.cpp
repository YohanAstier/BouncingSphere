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
