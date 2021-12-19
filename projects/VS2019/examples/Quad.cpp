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

	rlVertex3f(-1, 0, -1);
	rlVertex3f(-1, 0, 1);
	rlVertex3f(1, 0, -1);

	rlVertex3f(1, 0, -1);
	rlVertex3f(-1, 0, 1);
	rlVertex3f(1, 0, 1);

	rlVertex3f(-1, 0, 1);
	rlVertex3f(-1, 0, -1);
	rlVertex3f(1, 0, -1);

	rlVertex3f(-1, 0, 1);
	rlVertex3f(1, 0, -1);
	rlVertex3f(1, 0, 1);

	rlEnd();
	rlPopMatrix();
}

void MyDrawBox(Box box, Color color) {
	MyDrawQuadRotative(box.faces[0], color);
	MyDrawQuadRotative(box.faces[1], color);
	MyDrawQuadRotative(box.faces[2], color);
	MyDrawQuadRotative(box.faces[3], color);
	MyDrawQuadRotative(box.faces[4], color);
	MyDrawQuadRotative(box.faces[5], color);
}

Box CreateBox(Referential r, Vector3 extension) {
	Box box = { r, extension };
	// Face Up
	box.faces[0] = { changeReferential(r,Vector3Scale(r.j,extension.y),QuaternionIdentity()),{extension.x,0,extension.z} };
	// Face Down
	box.faces[1] = { changeReferential(r,Vector3Scale(r.j,-extension.y),QuaternionIdentity()),{extension.x,0,extension.z} };
	// Face Right
	box.faces[2] = { changeReferential(r,Vector3Scale(r.i,extension.x),QuaternionFromAxisAngle({ 0,0,-1 }, PI / 2)),{extension.y,0,extension.z} };
	// Face Left
	box.faces[3] = { changeReferential(r,Vector3Scale(r.i, -extension.x),QuaternionFromAxisAngle({ 0,0,1 }, PI / 2)),{extension.y,0,extension.z} };
	// Face Forward
	box.faces[4] = { changeReferential(r,Vector3Scale(r.k, extension.z),QuaternionFromAxisAngle({ 1,0,0 }, PI / 2)),{extension.x,0,extension.y} };
	// Face Back
	box.faces[5] = { changeReferential(r,Vector3Scale(r.k, -extension.z),QuaternionFromAxisAngle({ -1,0,0 }, PI / 2)),{extension.x,0,extension.y} };
	return box;
}

bool interSegBox(Box b, Segment s, Vector3* interPt, Vector3* interNorm) {
	for (int i = 0; i < 6; i++)
	{
		if (InterSegmentQuad(s, b.faces[i], interPt, interNorm)) return true;
	}
	return false;
}

RoundedBox CreateRoundedBox(Referential r, Vector3 extension, float rad) {
	RoundedBox rb;
	rb.r = rad;
	
	Box box = { r,extension };

	// Face Up
	box.faces[0] = { changeReferential(r,Vector3Scale(r.j,extension.y + rad),QuaternionIdentity()),{extension.x,0,extension.z} };
	// Face Down
	box.faces[1] = { changeReferential(r,Vector3Scale(r.j,-extension.y - rad),QuaternionIdentity()),{extension.x,0,extension.z} };
	// Face Right
	box.faces[2] = { changeReferential(r,Vector3Scale(r.i,extension.x + rad),QuaternionFromAxisAngle({ 0,0,-1 }, PI / 2)),{extension.y,0,extension.z} };
	// Face Left
	box.faces[3] = { changeReferential(r,Vector3Scale(r.i, -extension.x - rad),QuaternionFromAxisAngle({ 0,0,1 }, PI / 2)),{extension.y,0,extension.z} };
	// Face Forward
	box.faces[4] = { changeReferential(r,Vector3Scale(r.k, extension.z + rad),QuaternionFromAxisAngle({ 1,0,0 }, PI / 2)),{extension.x,0,extension.y} };
	// Face Back
	box.faces[5] = { changeReferential(r,Vector3Scale(r.k, -extension.z - rad),QuaternionFromAxisAngle({ -1,0,0 }, PI / 2)),{extension.x,0,extension.y} };
	
	rb.b = box;
	return rb;

}

bool interSegRoundedBox(RoundedBox rb, Segment s, Vector3* interPt, Vector3* interNorm) {
	if (interSegBox(rb.b, s, interPt, interNorm)){
		return true;
	}
	return false;
}

bool interDeplacementSphereRoundedBox(Segment s, Ball b, RoundedBox rb, Vector3* interPt, Vector3* interNorm) {
	int distance = INT16_MAX;
	Vector3 point;
	Vector3 norm;
	for (int i = 0; i < 6; i++)
	{
		if (InterSegmentQuad(s, rb.b.faces[i], interPt, interNorm)){
			if (Vector3Distance(*interPt, b.s.pos) < distance) {
				distance = Vector3Distance(*interPt, b.s.pos);
				point = *interPt;
				norm = *interNorm;
			}
		}
	}
	if (distance != INT16_MAX)
	{
		*interPt = point;
		*interNorm = norm;
		return true;
	}
	return false;
}