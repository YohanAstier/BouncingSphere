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
		MyDrawDisk({ 0,0,0,0 }, {0, 1, 0}, 1, nSegmentsTheta, color);
		MyDrawDisk({ 0,0,0,0 }, {0, 0, 0}, 1, nSegmentsTheta, color);
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
		MyDrawDiskWire({ 0,0,0,0 }, {0, 1, 0}, 1, nSegmentsTheta, color);
		MyDrawDiskWire({ 0,0,0,0 }, {0, 0, 0}, 1, nSegmentsTheta, color);
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
		MyDrawDiskWiresPortion({ 0,0,0,0 }, {0, 1, 0}, 1, startTheta, endTheta, nSegmentsTheta, color);
		MyDrawDiskWiresPortion({ 0,0,0,0 }, {0, 0, 0}, 1, startTheta, endTheta, nSegmentsTheta, color);
	}



	rlEnd();
	rlPopMatrix();

}

bool InterSegmentInfiniteCylinder(Segment seg, Cylinder cyl, Vector3* interPt, Vector3* interNormal) {
	Vector3 AB = Vector3Subtract(seg.pt2, seg.pt1);
	Vector3 PQ = Vector3Subtract(cyl.pt2, cyl.pt1);
	Vector3 PA = Vector3Subtract(seg.pt1, cyl.pt1);

	
	/*if ((AB.x == 0 && AB.y == 0) || PQ.x / AB.x == PQ.y / AB.y) {
		if (AB.z == 0 || PQ.x / AB.x == PQ.z / AB.z) {
			return false;
		}
	}*/

	Vector3 fact1 = Vector3Scale(PQ,(Vector3DotProduct(PQ, AB)/ Vector3DotProduct(PQ,PQ)));
	Vector3 i =	Vector3Subtract(AB,fact1);
	float a = Vector3DotProduct(i, i);
	Vector3 fact2 = Vector3Scale(PQ, (Vector3DotProduct(PQ, PA) / Vector3DotProduct(PQ, PQ)));
	Vector3 j = Vector3Subtract(PA, fact2);
	float b = Vector3DotProduct(i, j) * 2;
	float c = Vector3DotProduct(j, j) - (cyl.radius*cyl.radius);
	float delta = b*b - 4*a*c;
	
	if (delta < 0)
	{
		return false;
	}
	float ax = (-b + sqrt(delta)) / (2 * a);
	float bx = (-b - sqrt(delta)) / (2 * a);
	float x = ax > bx ? bx : ax;

	*interPt = Vector3Add(seg.pt1, Vector3Scale(AB, x));
	*interNormal = Vector3Negate(AB);
	
	return true;

	
}

bool InterSegmentInfiniteCylinder(Segment seg, Cylinder cyl, Vector3* interPt, Vector3* interNormal) {
	if (!InterSegmentInfiniteCylinder(seg, cyl, interPt, interNormal)) return false;

	//Verifier si la distance du point au cylindre est inférieure au rayon


}