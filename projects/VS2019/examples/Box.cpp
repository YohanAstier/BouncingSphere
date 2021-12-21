#include "Box.h"

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
	if (interSegBox(rb.b, s, interPt, interNorm)) {
		return true;
	}
	return false;
}