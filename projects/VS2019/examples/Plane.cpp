#include "Plane.h"

bool InterSegPlane(Segment s, Plane p, Vector3* interPt, Vector3* interNormalPt) {
	Vector3 ab = Vector3Subtract(s.pt2, s.pt1);
	float dotAB = Vector3DotProduct(ab, p.normal);
	if (fabs(dotAB < EPSILON)) return false;

	float t = (p.d - Vector3DotProduct(s.pt1, p.normal))/dotAB;
	if (t < 0 || t > 1) return false;

	*interPt = Vector3Add(s.pt1, Vector3Scale(ab, t));
	if (dotAB < 0) *interNormalPt = p.normal;
	else *interNormalPt = Vector3Negate(p.normal);

	return true;
}
