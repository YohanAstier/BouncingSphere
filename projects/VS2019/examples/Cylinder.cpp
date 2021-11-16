#include "Cylinder.h"

Cylindrical CartesianToCylindrical(Vector3 cart)
{
	Cylindrical cyl;
	cyl.rho = sqrtf(cart.x * cart.x + cart.z * cart.z);
	cyl.y = cart.y;

	if (cyl.rho < EPSILON)cyl.theta = 0;
	else
	{
		cyl.theta = atan2f(cart.x, cart.z);
		if (cyl.theta < 0)cyl.theta += PI * 2;
	}
	return cyl;
}

Vector3 CylindricalToCartesian(Cylindrical cyl)
{
	return Vector3{ cyl.rho * sinf(cyl.theta),cyl.y,cyl.rho * cosf(cyl.theta) };
}

void MyDrawCylinder(Quaternion q, Cylinder cyl, int nSegmentsTheta, bool drawCaps, Color color) {
	//on met en place l'espace de modélisation
	rlPushMatrix();

	rlTranslatef(cyl.pt1.x, cyl.pt1.y, cyl.pt1.z);

	Vector3 height = Vector3Subtract(cyl.pt2, cyl.pt1);
	float size = Vector3Length(height);

	rlScalef(cyl.radius, size, cyl.radius);
	float angle;
	Vector3 vector;
	QuaternionToAxisAngle(q, &vector, &angle);


	rlRotatef(angle * RAD2DEG, vector.x, vector.y, vector.z);



	rlColor4ub(color.r, color.g, color.b, color.a);

	float deltaTheta = 2 * PI / nSegmentsTheta;

	//on dessine chaque triangle
	for (int i = 0; i < nSegmentsTheta; i++) {
		Vector3 p1 = SphericalToCartesian(Spherical{
			1, i * deltaTheta, PI / 2
			});
		int y = i + 1;
		Vector3 p2 = SphericalToCartesian(Spherical{
			1, y * deltaTheta, PI / 2
			});


		//on effectue 2 triangles pour constituer un rectangle
		// et 2 fois pour chaque coté du cylindre
		rlBegin(RL_TRIANGLES);
		rlVertex3f(p1.x, 1, p1.z);
		rlVertex3f(p2.x, 0, p2.z);
		rlVertex3f(p2.x, 1, p2.z);

		rlVertex3f(p2.x, 0, p2.z);
		rlVertex3f(p1.x, 1, p1.z);
		rlVertex3f(p2.x, 1, p2.z);

		rlVertex3f(p1.x, 1, p1.z);
		rlVertex3f(p1.x, 0, p1.z);
		rlVertex3f(p2.x, 0, p2.z);

		rlVertex3f(p1.x, 0, p1.z);
		rlVertex3f(p1.x, 1, p1.z);
		rlVertex3f(p2.x, 0, p2.z);

	}
	if (drawCaps) {
		//on rajoute les extrémités si souhaité
		MyDrawDisk({ 0,0,0,0 }, cyl.pt2, 1, nSegmentsTheta, color);
		MyDrawDisk({ 0,0,0,0 }, cyl.pt1, 1, nSegmentsTheta, color);
	}

	rlEnd();
	rlPopMatrix();

};

void MyDrawCylinderWire(Quaternion q, Cylinder cyl, int nSegmentsTheta, bool drawCaps, Color color) {
	//on met en place l'espace de modélisation
	rlPushMatrix();

	rlTranslatef(cyl.pt1.x, cyl.pt1.y, cyl.pt1.z);

	Vector3 height = Vector3Subtract(cyl.pt2, cyl.pt1);
	float size = Vector3Length(height);

	rlScalef(cyl.radius, size, cyl.radius);
	float angle;
	Vector3 vector;
	QuaternionToAxisAngle(q, &vector, &angle);


	rlRotatef(angle * RAD2DEG, vector.x, vector.y, vector.z);



	rlColor4ub(color.r, color.g, color.b, color.a);

	float deltaTheta = 2 * PI / nSegmentsTheta;

	//on dessine chaque triangle
	for (int i = 0; i < nSegmentsTheta; i++) {
		Vector3 p1 = SphericalToCartesian(Spherical{
			1, i * deltaTheta, PI / 2
			});
		int y = i + 1;
		Vector3 p2 = SphericalToCartesian(Spherical{
			1, y * deltaTheta, PI / 2
			});


		// et 2 fois pour chaque coté du cylindre
		rlBegin(RL_LINES);
		//triangle 1
		rlVertex3f(p1.x, 1, p1.z);
		rlVertex3f(p2.x, 0, p2.z);

		rlVertex3f(p1.x, 1, p1.z);
		rlVertex3f(p2.x, 1, p2.z);

		rlVertex3f(p2.x, 0, p2.z);
		rlVertex3f(p2.x, 1, p2.z);

		//triangle 2
		rlVertex3f(p2.x, 0, p2.z);
		rlVertex3f(p1.x, 1, p1.z);

		rlVertex3f(p2.x, 0, p2.z);
		rlVertex3f(p2.x, 1, p2.z);

		rlVertex3f(p1.x, 1, p1.z);
		rlVertex3f(p2.x, 1, p2.z);

	}
	if (drawCaps) {
		//on rajoute les extrémités si souhaité
		MyDrawDiskWire({ 0,0,0,0 }, cyl.pt2, 1, nSegmentsTheta, color);
		MyDrawDiskWire({ 0,0,0,0 }, cyl.pt1, 1, nSegmentsTheta, color);
	}

	rlEnd();
	rlPopMatrix();

};


void MyDrawCylinderPortion(Quaternion q, Cylinder cyl, float startTheta, float endTheta, int nSegmentsTheta, bool drawCaps, Color color) {
	//on met en place l'espace de modélisation
	rlPushMatrix();

	

	
	float angle;
	Vector3 vector;
	QuaternionToAxisAngle(q, &vector, &angle);


	rlRotatef(angle * RAD2DEG, vector.x, vector.y, vector.z);

	Vector3 height = Vector3Subtract(cyl.pt2, cyl.pt1);
	float size = Vector3Length(height);
	printf("%f", size);

	rlScalef(cyl.radius, size, cyl.radius);
	rlTranslatef(cyl.pt1.x, cyl.pt1.y, cyl.pt1.z);


	rlColor4ub(color.r, color.g, color.b, color.a);

	float deltaTheta = 2 * PI / nSegmentsTheta;

	//on dessine chaque triangle
	for (int i = startTheta; i < endTheta; i++) {
		Vector3 p1 = SphericalToCartesian(Spherical{
			1, i * deltaTheta, PI / 2
			});
		int y = i + 1;
		Vector3 p2 = SphericalToCartesian(Spherical{
			1, y * deltaTheta, PI / 2
			});


		//on effectue 2 triangles pour constituer un rectangle
		// et 2 fois pour chaque coté du cylindre
		rlBegin(RL_TRIANGLES);
		rlVertex3f(p1.x, 1, p1.z);
		rlVertex3f(p2.x, 0, p2.z);
		rlVertex3f(p2.x, 1, p2.z);

		rlVertex3f(p2.x, 0, p2.z);
		rlVertex3f(p1.x,1, p1.z);
		rlVertex3f(p2.x, 1, p2.z);

		rlVertex3f(p1.x, 1, p1.z);
		rlVertex3f(p1.x, 0, p1.z);
		rlVertex3f(p2.x, 0, p2.z);

		rlVertex3f(p1.x, 1, p1.z);
		rlVertex3f(p1.x, 0, p1.z);
		rlVertex3f(p2.x, 0, p2.z);

	}
	if (drawCaps) {
		//on rajoute les extrémités si souhaité
		MyDrawDiskPortion({ 0,0,0,0 }, { 0,1,0 }, 1, startTheta, endTheta, nSegmentsTheta, color);
		MyDrawDiskPortion({ 0,0,0,0 }, { 0,0,0 } , 1, startTheta, endTheta, nSegmentsTheta, color);
	}

	rlEnd();
	rlPopMatrix();
}

void MyDrawCylinderWiresPortion(Quaternion q, Cylinder cyl, float startTheta, float endTheta, int nSegmentsTheta, bool drawCaps, Color color) {
	rlPushMatrix();

	rlTranslatef(cyl.pt1.x, cyl.pt1.y, cyl.pt1.z);

	Vector3 height = Vector3Subtract(cyl.pt2, cyl.pt1);
	float size = Vector3Length(height);

	rlScalef(cyl.radius, size, cyl.radius);
	float angle;
	Vector3 vector;
	QuaternionToAxisAngle(q, &vector, &angle);


	rlRotatef(angle * RAD2DEG, vector.x, vector.y, vector.z);



	rlColor4ub(color.r, color.g, color.b, color.a);

	float deltaTheta = 2 * PI / nSegmentsTheta;

	//on dessine chaque triangle
	for (int i = startTheta; i < endTheta; i++) {
		Vector3 p1 = SphericalToCartesian(Spherical{
			1, i * deltaTheta, PI / 2
			});
		int y = i + 1;
		Vector3 p2 = SphericalToCartesian(Spherical{
			1, y * deltaTheta, PI / 2
			});


		// et 2 fois pour chaque coté du cylindre
		rlBegin(RL_LINES);
		//triangle 1
		rlVertex3f(p1.x, 1, p1.z);
		rlVertex3f(p2.x, 0, p2.z);

		rlVertex3f(p1.x, 1, p1.z);
		rlVertex3f(p2.x, 1, p2.z);

		rlVertex3f(p2.x, 0, p2.z);
		rlVertex3f(p2.x, 1, p2.z);

		//triangle 2
		rlVertex3f(p2.x, 0, p2.z);
		rlVertex3f(p1.x, 1, p1.z);

		rlVertex3f(p2.x, 0, p2.z);
		rlVertex3f(p2.x, 1, p2.z);

		rlVertex3f(p1.x, 1, p1.z);
		rlVertex3f(p2.x, 1, p2.z);

	}
	if (drawCaps) {
		//on rajoute les extrémités si souhaité
		MyDrawDiskWiresPortion({ 0,0,0,0 }, cyl.pt2, 1, startTheta, endTheta, nSegmentsTheta, color);
		MyDrawDiskWiresPortion({ 0,0,0,0 }, cyl.pt1, 1, startTheta, endTheta, nSegmentsTheta, color);
	}

	rlEnd();
	rlPopMatrix();

}