#include "Disk.h"

void MyDrawDiskWire(Quaternion q, Vector3 center, float radius, int nSegmentsTheta, Color color) {
	rlPushMatrix();
	rlRotatef(q.w * RAD2DEG, q.x, q.y, q.z);
	rlScalef(radius, radius, radius);
	rlBegin(RL_LINES);
	rlColor4ub(color.r, color.g, color.b, color.a);
	float deltaTheta = 2 * PI / nSegmentsTheta;
	for (int i = 0; i < nSegmentsTheta; i++) {
		Vector3 p1 = SphericalToCartesian(Spherical{
			1, i * deltaTheta, PI / 2
			});
		int y = i + 1;
		Vector3 p2 = SphericalToCartesian(Spherical{
			1, y * deltaTheta, PI / 2
			});

		rlVertex3f(0, center.y, 0);
		rlVertex3f(p1.x, center.y, p1.z);

		rlVertex3f(0, center.y, 0);
		rlVertex3f(p2.x, center.y, p2.z);

		rlVertex3f(p1.x, center.y, p1.z);
		rlVertex3f(p2.x, center.y, p2.z);

	}

	rlEnd();
	rlPopMatrix();

}

void MyDrawDiskPortion(Quaternion q, Vector3 center, float radius, float startTheta, float endTheta, int nSegmentsTheta, Color color) {
	rlPushMatrix();
	rlRotatef(q.w * RAD2DEG, q.x, q.y, q.z);
	rlScalef(radius, radius, radius);

	rlColor4ub(color.r, color.g, color.b, color.a);
	float deltaTheta = 2 * PI / nSegmentsTheta;
	for (int i = startTheta; i < endTheta; i++) {
		Vector3 p1 = SphericalToCartesian(Spherical{
			1, i * deltaTheta, PI / 2
			});
		int y = i + 1;
		Vector3 p2 = SphericalToCartesian(Spherical{
			1, y * deltaTheta, PI / 2
			});
		rlBegin(RL_TRIANGLES);
		rlVertex3f(0, center.y, 0);
		rlVertex3f(p1.x, center.y, p1.z);
		rlVertex3f(p2.x, center.y, p2.z);

		rlVertex3f(p1.x, center.y, p1.z);
		rlVertex3f(0, center.y, 0);
		rlVertex3f(p2.x, center.y, p2.z);
	}

	rlEnd();
	rlPopMatrix();

}

void MyDrawDisk(Quaternion q, Vector3 center, float radius, int nSegmentsTheta, Color color) {
	rlPushMatrix();
	rlRotatef(q.w * RAD2DEG, q.x, q.y, q.z);
	rlScalef(radius, radius, radius);

	rlColor4ub(color.r, color.g, color.b, color.a);
	float deltaTheta = 2 * PI / nSegmentsTheta;
	for (int i = 0; i < nSegmentsTheta; i++) {
		Vector3 p1 = SphericalToCartesian(Spherical{
			1, i * deltaTheta, PI / 2
			});
		int y = i + 1;
		Vector3 p2 = SphericalToCartesian(Spherical{
			1, y * deltaTheta, PI / 2
			});
		rlBegin(RL_TRIANGLES);
		rlVertex3f(0, center.y, 0);
		rlVertex3f(p1.x, center.y, p1.z);
		rlVertex3f(p2.x, center.y, p2.z);

		rlVertex3f(p1.x, center.y, p1.z);
		rlVertex3f(0, center.y, 0);
		rlVertex3f(p2.x, center.y, p2.z);
	}

	rlEnd();
	rlPopMatrix();

}

void MyDrawDiskWiresPortion(Quaternion q, Vector3 center, float radius, float startTheta, float endTheta, int nSegmentsTheta, Color color) {
	rlPushMatrix();
	rlRotatef(q.w * RAD2DEG, q.x, q.y, q.z);
	rlScalef(radius, radius, radius);
	rlBegin(RL_LINES);
	rlColor4ub(color.r, color.g, color.b, color.a);
	float deltaTheta = 2 * PI / nSegmentsTheta;
	for (int i = startTheta; i < endTheta; i++) {
		Vector3 p1 = SphericalToCartesian(Spherical{
			1, i * deltaTheta, PI / 2
			});
		int y = i + 1;
		Vector3 p2 = SphericalToCartesian(Spherical{
			1, y * deltaTheta, PI / 2
			});

		rlVertex3f(0, center.y, 0);
		rlVertex3f(p1.x, center.y, p1.z);

		rlVertex3f(0, center.y, 0);
		rlVertex3f(p2.x, center.y, p2.z);

		rlVertex3f(p1.x, center.y, p1.z);
		rlVertex3f(p2.x, center.y, p2.z);

	}

	rlEnd();
	rlPopMatrix();

}