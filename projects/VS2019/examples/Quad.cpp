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
	return (abs(localPoint.x) <=  quad.extension.x
		 && abs(localPoint.z) <= quad.extension.z);
}

void MyDrawQuadRotative(Quad quad, Color color) {
	rlPushMatrix();

	float angle;
	Vector3 vector;

	rlTranslatef(quad.r.origin.x, quad.r.origin.y, quad.r.origin.z);

	QuaternionToAxisAngle(quad.r.quat, &vector, &angle);
	rlRotatef(angle * RAD2DEG, vector.x, vector.y, vector.z);

	rlScalef(quad.extension.x, quad.extension.y, quad.extension.z);



	rlColor4ub(color.r, color.g, color.b, color.a);

	rlBegin(RL_TRIANGLES);

	rlVertex3f(0, -1, 0);
	rlVertex3f(0, -1, 1);
	rlVertex3f(1, -1, 1);

	//triangle 2
	rlVertex3f(0, -1, 0);
	rlVertex3f(1, -1, 1);
	rlVertex3f(0, -1, 1);

	//triangle 3
	rlVertex3f(0, -1, 0);
	rlVertex3f(1, -1, 0);
	rlVertex3f(1, -1, 1);

	//triangle 4
	rlVertex3f(0, -1, 0);
	rlVertex3f(1, -1, 1);
	rlVertex3f(1, -1, 0);


	rlEnd();
	rlPopMatrix();
}

void MyDrawBox(Box box) {


}

Box CreateBox(Referencial r, Vector3 extension) {
	float minHeight;
	if (extension.x != extension.z) {
		if (extension.x < extension.z) {
			minHeight = extension.x;
		}
		else {
			minHeight = extension.z;
		}
	}
	else {
		minHeight = extension.x;
	}

	Quad faces[6];
	Quad q = { r, extension };
	faces[0] = q;

	Quaternion quat2 = QuaternionFromAxisAngle(Vector3Normalize({ -1,0,0 }), PI / 2);
	Referencial r2 = ReferencialByQuarternion(r, quat2);
	Quad q2;
	if (extension.x < extension.z) {

		q2 = { r2, {minHeight,0,minHeight} };
	}
	else {
		q2 = { r2, extension };
	}
	faces[1] = q2;
	Quaternion quat3 = QuaternionFromAxisAngle(Vector3Normalize({ 0,0,1 }), PI / 2);
	Referencial r3 = ReferencialByQuarternion(r, quat3);
	Quad q3;
	if (extension.x > extension.z) {

		q3 = { r3, {minHeight,0,minHeight} };
	}
	else {
		q3 = { r3, extension };
	}
	faces[2] = q3;

	Quaternion quat4 = r.quat;
	Referencial r4 = { 
		{r.origin.x,minHeight + r.origin.y,r.origin.z},
		{r.origin.x + extension.x,minHeight + r.origin.y,r.origin.z},
		{r.origin.x,minHeight*2 + r.origin.y,r.origin.z + extension.z},
		{r.origin.x,minHeight + r.origin.y,extension.z}, QuaternionIdentity() };
	r4 = ReferencialByQuarternion(r4, quat4);
	Quad q4 = { r4, extension };
	faces[3] = q4;
	Quaternion quat5 = QuaternionFromAxisAngle(Vector3Normalize({ 0,0,1 }), PI / 2);
	Referencial r5 = { 
		{extension.x + r.origin.x,r.origin.y,r.origin.z},
		{extension.x*2 + r.origin.x,r.origin.y,r.origin.z},
		{extension.x + r.origin.x,minHeight + r.origin.y,r.origin.z},
		{extension.x + r.origin.x,r.origin.y,extension.y + r.origin.z}, QuaternionIdentity() };
	r5 = ReferencialByQuarternion(r5, r.quat);
	r5 = ReferencialByQuarternion(r5, quat5);
	Quad q5;
	if (extension.x > extension.z) {

		q5 = { r5, {minHeight,0,minHeight} };
	}
	else {
		q5 = { r5, extension };
	}
	faces[4] = q5;
	Quaternion quat6 = QuaternionFromAxisAngle(Vector3Normalize({ -1,0,0 }), PI / 2);
	Referencial r6 = { 
		{r.origin.x,r.origin.y,extension.z + r.origin.z},
		{extension.x,r.origin.y,extension.z + r.origin.z},
		{r.origin.x,minHeight,extension.z + r.origin.z},
		{r.origin.x,r.origin.y,extension.y*2 + r.origin.z}, QuaternionIdentity() };
	r6 = ReferencialByQuarternion(r6, r.quat);
	r6 = ReferencialByQuarternion(r6, quat6);
	Quad q6;
	if (extension.x < extension.z) {

		q6 = { r6, {minHeight,0,minHeight} };
	}
	else {
		q6 = { r6, {extension.x,0,minHeight} };
	}
	faces[5] = q6;
	Box box = { r, extension, faces };
	return box;
}