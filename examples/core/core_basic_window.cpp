/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <raymath.h>
#include "rlgl.h"
#include <math.h>
#include <float.h>
#include <vector>

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

#define EPSILON 1.e-6f

void MyDrawSphereEx(Vector3 centerPos, float radius, int rings, int slices, Color color);
void MyDrawDisk(Quaternion q, Vector3 center, float radius, int nSegmentsTheta, Color color);

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

struct Cylinder
{
	Vector3 pt1;
	Vector3 pt2;
	float radius;
};

struct Sphere {
	Vector3 pos;
	float r;
};

struct Cylindrical {
	float rho;
	float theta;
	float y;

	inline Cylindrical operator+(Cylindrical a) {
		return { a.rho + rho,a.theta + theta,a.y + y };
	}
};

struct Spherical {
	float rho;
	float theta;
	float phi;

	inline Spherical operator+(Spherical a) {
		return { a.rho + rho,a.theta + theta,a.phi + phi };
	}

};

struct Segment {
	Vector3 pt1;
	Vector3 pt2;
};

struct Plane {
	Vector3 normal;
	float d;
};

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

Vector3 SphericalToCartesian(Spherical sph)
{
	return Vector3{ sph.rho * sinf(sph.phi) * sinf(sph.theta),
	sph.rho * cosf(sph.phi),
	sph.rho * sinf(sph.phi) * cosf(sph.theta) };
}

void MyUpdateOrbitalCamera(Camera* camera, float deltaTime)
{
	static Spherical sphPos = { 10,PI / 4.f,PI / 4.f };
	static Spherical sphSpeed = { 10,.4f,.4f };
	float rhoMin = 4;
	float rhoMax = 40;

	static Vector2 prevMousePos = { 0,0 };
	Vector2 mousePos = GetMousePosition();
	Vector2 mouseVect = Vector2Subtract(mousePos, prevMousePos);
	prevMousePos = mousePos;

	Spherical sphDelta = { -GetMouseWheelMove() * sphSpeed.rho * deltaTime *4,
	IsMouseButtonDown(MOUSE_RIGHT_BUTTON) ? mouseVect.x * sphSpeed.theta * deltaTime : 0,
	IsMouseButtonDown(MOUSE_RIGHT_BUTTON) ? mouseVect.y * sphSpeed.phi * deltaTime : 0 };

	Spherical newSphPos = sphPos + sphDelta;
	newSphPos = { Clamp(newSphPos.rho,rhoMin,rhoMax),
	newSphPos.theta,
	Clamp(newSphPos.phi,PI / 100.f,.99f * PI) };

	sphPos = newSphPos;

	camera->position = SphericalToCartesian(sphPos);

}

void MyDrawSphereEx2(Quaternion q, Vector3 centerPos, float radius, int nSegmentsTheta, int nSegmentsPhi, Color color)
{
	if (nSegmentsTheta < 3 || nSegmentsPhi < 2) return;

	std::vector<Vector3> vertexBufferTheta(nSegmentsTheta + 1);
	std::fill(vertexBufferTheta.begin(), vertexBufferTheta.end(), Vector3{ 0,1,0 });

	int numVertex = nSegmentsTheta * nSegmentsPhi * 6;
	if (rlCheckBufferLimit(numVertex)) rlglDraw();

	rlPushMatrix();

	// NOTE: Transformation is applied in inverse order (scale -> translate)
	rlTranslatef(centerPos.x, centerPos.y, centerPos.z);

	//ROTATION
	Vector3 vect;
	float angle;
	QuaternionToAxisAngle(q, &vect, &angle);
	rlRotatef(angle * RAD2DEG, vect.x, vect.y, vect.z);
	//

	rlScalef(radius, radius, radius);


	rlBegin(RL_TRIANGLES);
	rlColor4ub(color.r, color.g, color.b, color.a);

	float deltaPhi = PI / nSegmentsPhi;
	float deltaTheta = 2 * PI / nSegmentsTheta;

	float phi = 0;
	for (int i = 0; i < nSegmentsPhi; i++)
	{
		float theta = 0;
		Vector3 tmpBottomLeft = SphericalToCartesian(Spherical{ 1,theta,phi + deltaPhi });

		for (int j = 0; j < nSegmentsTheta; j++)
		{
			Vector3 topLeft = vertexBufferTheta[j];
			Vector3 bottomLeft = tmpBottomLeft;
			Vector3 topRight = vertexBufferTheta[j + 1];
			Vector3 bottomRight = SphericalToCartesian(Spherical{ 1,theta + deltaTheta,phi + deltaPhi });


			rlVertex3f(bottomLeft.x, bottomLeft.y, bottomLeft.z);
			rlVertex3f(topRight.x, topRight.y, topRight.z);
			rlVertex3f(topLeft.x, topLeft.y, topLeft.z);

			rlVertex3f(bottomLeft.x, bottomLeft.y, bottomLeft.z);
			rlVertex3f(bottomRight.x, bottomRight.y, bottomRight.z);
			rlVertex3f(topRight.x, topRight.y, topRight.z);

			theta += deltaTheta;

			vertexBufferTheta[j] = tmpBottomLeft;
			tmpBottomLeft = bottomRight;
		}
		vertexBufferTheta[vertexBufferTheta.size() - 1] = vertexBufferTheta[0];
		phi += deltaPhi;
	}
	rlEnd();
	rlPopMatrix();
}

void MyDrawSphereWiresEx2(Quaternion q, Vector3 centerPos, float radius, int nSegmentsTheta, int nSegmentsPhi, Color color)
{
	if (nSegmentsTheta < 3 || nSegmentsPhi < 2) return;

	std::vector<Vector3> vertexBufferTheta(nSegmentsTheta + 1);
	std::fill(vertexBufferTheta.begin(), vertexBufferTheta.end(), Vector3{ 0,1,0 });

	int numVertex = nSegmentsTheta * nSegmentsPhi * 4;
	if (rlCheckBufferLimit(numVertex)) rlglDraw();

	rlPushMatrix();
	// NOTE: Transformation is applied in inverse order (scale -> translate)
	rlTranslatef(centerPos.x, centerPos.y, centerPos.z);

	//ROTATION
	Vector3 vect;
	float angle;
	QuaternionToAxisAngle(q, &vect, &angle);
	rlRotatef(angle * RAD2DEG, vect.x, vect.y, vect.z);
	//

	rlScalef(radius, radius, radius);

	rlBegin(RL_LINES);
	rlColor4ub(color.r, color.g, color.b, color.a);

	float deltaPhi = PI / nSegmentsPhi;
	float deltaTheta = 2 * PI / nSegmentsTheta;

	float phi = 0;
	for (int i = 0; i < nSegmentsPhi; i++)
	{
		float theta = 0;

		for (int j = 0; j < nSegmentsTheta; j++)
		{
			Vector3 topLeft = vertexBufferTheta[j];
			Vector3 bottomLeft = SphericalToCartesian(Spherical{ 1,theta,phi + deltaPhi });
			Vector3 topRight = vertexBufferTheta[j + 1];

			rlVertex3f(topLeft.x, topLeft.y, topLeft.z);
			rlVertex3f(topRight.x, topRight.y, topRight.z);

			rlVertex3f(topLeft.x, topLeft.y, topLeft.z);
			rlVertex3f(bottomLeft.x, bottomLeft.y, bottomLeft.z);

			theta += deltaTheta;

			vertexBufferTheta[j] = bottomLeft;
		}
		vertexBufferTheta[vertexBufferTheta.size() - 1] = vertexBufferTheta[0];
		phi += deltaPhi;
	}
	rlEnd();
	rlPopMatrix();
}

void MyDrawSphereEx2(Vector3 centerPos, float radius, int nSegmentsTheta, int nSegmentsPhi, Color color)
{
	if (nSegmentsTheta < 3 || nSegmentsPhi < 2) return;

	std::vector<Vector3> vertexBufferTheta(nSegmentsTheta + 1);
	std::fill(vertexBufferTheta.begin(), vertexBufferTheta.end(), Vector3{ 0,radius,0 });

	int numVertex = nSegmentsTheta * nSegmentsPhi * 6;
	if (rlCheckBufferLimit(numVertex)) rlglDraw();

	rlPushMatrix();
	// NOTE: Transformation is applied in inverse order (scale -> translate)
	rlTranslatef(centerPos.x, centerPos.y, centerPos.z);
	rlScalef(radius, radius, radius);

	rlBegin(RL_TRIANGLES);
	rlColor4ub(color.r, color.g, color.b, color.a);

	float deltaPhi = PI / nSegmentsPhi;
	float deltaTheta = 2 * PI / nSegmentsTheta;

	float phi = 0;
	for (int i = 0; i < nSegmentsPhi; i++)
	{
		float theta = 0;
		Vector3 tmpBottomLeft = SphericalToCartesian(Spherical{ radius,theta,phi + deltaPhi });

		for (int j = 0; j < nSegmentsTheta; j++)
		{
			Vector3 topLeft = vertexBufferTheta[j];
			Vector3 bottomLeft = tmpBottomLeft;
			Vector3 topRight = vertexBufferTheta[j + 1];
			Vector3 bottomRight = SphericalToCartesian(Spherical{ radius,theta + deltaTheta,phi + deltaPhi });


			rlVertex3f(bottomLeft.x, bottomLeft.y, bottomLeft.z);
			rlVertex3f(topRight.x, topRight.y, topRight.z);
			rlVertex3f(topLeft.x, topLeft.y, topLeft.z);

			rlVertex3f(bottomLeft.x, bottomLeft.y, bottomLeft.z);
			rlVertex3f(bottomRight.x, bottomRight.y, bottomRight.z);
			rlVertex3f(topRight.x, topRight.y, topRight.z);

			theta += deltaTheta;

			vertexBufferTheta[j] = tmpBottomLeft;
			tmpBottomLeft = bottomRight;
		}
		vertexBufferTheta[vertexBufferTheta.size() - 1] = vertexBufferTheta[0];
		phi += deltaPhi;
	}
	rlEnd();
	rlPopMatrix();
}

void MyDrawSphereWiresEx2(Vector3 centerPos, float radius, int nSegmentsTheta, int nSegmentsPhi, Color color)
{
	if (nSegmentsTheta < 3 || nSegmentsPhi < 2) return;

	std::vector<Vector3> vertexBufferTheta(nSegmentsTheta + 1);
	std::fill(vertexBufferTheta.begin(), vertexBufferTheta.end(), Vector3{ 0,radius,0 });

	int numVertex = nSegmentsTheta * nSegmentsPhi * 4;
	if (rlCheckBufferLimit(numVertex)) rlglDraw();

	rlPushMatrix();
	// NOTE: Transformation is applied in inverse order (scale -> translate)
	rlTranslatef(centerPos.x, centerPos.y, centerPos.z);
	rlScalef(radius, radius, radius);

	rlBegin(RL_LINES);
	rlColor4ub(color.r, color.g, color.b, color.a);

	float deltaPhi = PI / nSegmentsPhi;
	float deltaTheta = 2 * PI / nSegmentsTheta;

	float phi = 0;
	for (int i = 0; i < nSegmentsPhi; i++)
	{
		float theta = 0;

		for (int j = 0; j < nSegmentsTheta; j++)
		{
			Vector3 topLeft = vertexBufferTheta[j];
			Vector3 bottomLeft = SphericalToCartesian(Spherical{ radius,theta,phi + deltaPhi });
			Vector3 topRight = vertexBufferTheta[j + 1];

			rlVertex3f(topLeft.x, topLeft.y, topLeft.z);
			rlVertex3f(topRight.x, topRight.y, topRight.z);

			rlVertex3f(topLeft.x, topLeft.y, topLeft.z);
			rlVertex3f(bottomLeft.x, bottomLeft.y, bottomLeft.z);

			theta += deltaTheta;

			vertexBufferTheta[j] = bottomLeft;
		}
		vertexBufferTheta[vertexBufferTheta.size() - 1] = vertexBufferTheta[0];
		phi += deltaPhi;
	}
	rlEnd();
	rlPopMatrix();
}


void MyDrawSphereTrianglesAndWiresEx(Vector3 centerPos, float radius, int nSegmentsTheta, int nSegmentsPhi, Color trianglesColor, Color wiresColor)
{
	if (nSegmentsTheta < 3 || nSegmentsPhi < 2) return;

	std::vector<Vector3> vertexBufferTheta(nSegmentsTheta + 1);
	std::fill(vertexBufferTheta.begin(), vertexBufferTheta.end(), Vector3{ 0,radius,0 });

	int numVertex = nSegmentsTheta * nSegmentsPhi * 10;
	if (rlCheckBufferLimit(numVertex)) rlglDraw();

	rlPushMatrix();
	// NOTE: Transformation is applied in inverse order (scale -> translate)
	rlTranslatef(centerPos.x, centerPos.y, centerPos.z);
	rlScalef(radius, radius, radius);


	float deltaPhi = PI / nSegmentsPhi;
	float deltaTheta = 2 * PI / nSegmentsTheta;

	float phi = 0;
	for (int i = 0; i < nSegmentsPhi; i++)
	{
		float theta = 0;
		Vector3 tmpBottomLeft = SphericalToCartesian(Spherical{ radius,theta,phi + deltaPhi });

		for (int j = 0; j < nSegmentsTheta; j++)
		{
			Vector3 topLeft = vertexBufferTheta[j];
			Vector3 bottomLeft = tmpBottomLeft;
			Vector3 topRight = vertexBufferTheta[j + 1];
			Vector3 bottomRight = SphericalToCartesian(Spherical{ radius,theta + deltaTheta,phi + deltaPhi });

			rlBegin(RL_TRIANGLES);
			rlColor4ub(trianglesColor.r, trianglesColor.g, trianglesColor.b, trianglesColor.a);

			rlVertex3f(bottomLeft.x, bottomLeft.y, bottomLeft.z);
			rlVertex3f(topRight.x, topRight.y, topRight.z);
			rlVertex3f(topLeft.x, topLeft.y, topLeft.z);

			rlVertex3f(bottomLeft.x, bottomLeft.y, bottomLeft.z);
			rlVertex3f(bottomRight.x, bottomRight.y, bottomRight.z);
			rlVertex3f(topRight.x, topRight.y, topRight.z);
			rlEnd();


			rlBegin(RL_LINES);
			rlColor4ub(wiresColor.r, wiresColor.g, wiresColor.b, wiresColor.a);
			rlVertex3f(bottomLeft.x, bottomLeft.y, bottomLeft.z); 
			rlVertex3f(topLeft.x, topLeft.y, topLeft.z);

			rlVertex3f(topLeft.x, topLeft.y, topLeft.z);
			rlVertex3f(topRight.x, topRight.y, topRight.z);
			rlEnd();


			theta += deltaTheta;

			vertexBufferTheta[j] = tmpBottomLeft;
			tmpBottomLeft = bottomRight;
		}
		vertexBufferTheta[vertexBufferTheta.size() - 1] = vertexBufferTheta[0];
		phi += deltaPhi;
	}

	rlPopMatrix();
}

bool InterSegPlane(Segment s, Plane p, Vector3* interPt, Vector3* interNormalPt) {
	Vector3 ab = Vector3Subtract(s.pt2, s.pt1);
	float dotAB = Vector3DotProduct(ab, p.normal);
	if (fabs(dotAB < EPSILON)) return false;

	float t = (p.d - Vector3DotProduct(s.pt1, p.normal));
	if (t < 0 || t > 1) return false;

	*interPt = Vector3Add(s.pt1, Vector3Scale(ab, t));
	if (dotAB < 0) *interNormalPt = p.normal;
	else *interNormalPt = Vector3Multiply({ -1,-1,-1 }, p.normal);

	return true;
}

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

bool InterSegmentSphere(Segment seg, Sphere s, Vector3* interPt) {
	Vector3 AB = Vector3Subtract(seg.pt2, seg.pt1);
	Vector3 OA = Vector3Subtract(seg.pt1, s.pos);
	
	double a = Vector3DotProduct(AB, AB);
	double b = 2 * Vector3DotProduct(AB, OA);
	double c = Vector3DotProduct(OA, OA) - pow(s.r, 2);

	double delt = pow(b, 2) - 4*a*c;

	if (delt < 0) return false;
	double x;
	if (delt == 0) {
		x = -b / 2 * a;
	}else {
		double ax = (-b + sqrt(delt)) / 2 * a;
		double bx = (-b - sqrt(delt)) / 2 * a;
		x = ax > bx ? bx : ax; 
	}
	*interPt = Vector3Add(seg.pt1, Vector3Scale(AB, x));
	return true;

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
		rlVertex3f(p1.x, cyl.pt2.y, p1.z);
		rlVertex3f(p2.x, cyl.pt1.y, p2.z);
		rlVertex3f(p2.x, cyl.pt2.y, p2.z);

		rlVertex3f(p2.x, cyl.pt1.y, p2.z);
		rlVertex3f(p1.x, cyl.pt2.y, p1.z);
		rlVertex3f(p2.x, cyl.pt2.y, p2.z);

		rlVertex3f(p1.x, cyl.pt2.y, p1.z);
		rlVertex3f(p1.x, cyl.pt1.y, p1.z);
		rlVertex3f(p2.x, cyl.pt1.y, p2.z);

		rlVertex3f(p1.x, cyl.pt1.y, p1.z);
		rlVertex3f(p1.x, cyl.pt2.y, p1.z);
		rlVertex3f(p2.x, cyl.pt1.y, p2.z);

	}
	if (drawCaps) {
		//on rajoute les extrémités si souhaité
		MyDrawDisk({ 0,0,0,0 }, cyl.pt2, 2, 1, color);
		MyDrawDisk({ 0,0,0,0 }, cyl.pt1, 1, nSegmentsTheta, color);
	}

	rlEnd();
	rlPopMatrix();
	
};

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

int main(int argc, char* argv[])
{
	// Initialization
	//--------------------------------------------------------------------------------------
	float screenSizeCoef = 1.4f;
	const int screenWidth = 1000 * screenSizeCoef;
	const int screenHeight = 820 * screenSizeCoef;

	InitWindow(screenWidth, screenHeight, "Bouncy Sphere");

	SetTargetFPS(60);

	//CAMERA
	Vector3 cameraPos = { 8.0f, 15.0f, 14.0f };
	Camera camera = { 0 };
	camera.position = cameraPos;
	camera.target = { 0.0f, 0.0f, 0.0f };
	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.f;
	camera.type = CAMERA_PERSPECTIVE;
	SetCameraMode(camera, CAMERA_CUSTOM);  // Set an orbital camera mode

	//TEST CONVERSION CARTESIAN->CYLINDRICAL
	Vector3 pos = { 1,1,1 };
	Cylindrical cyl = CartesianToCylindrical(pos);
	printf("cyl = (%f,%f,%f) ", cyl.rho, cyl.theta, cyl.y);
	cyl = cyl + cyl;
	printf("cyl = (%f,%f,%f) ", cyl.rho, cyl.theta, cyl.y);

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		float deltaTime = GetFrameTime();
		float time = (float)GetTime();

		MyUpdateOrbitalCamera(&camera, deltaTime);

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode3D(camera);
		{
			//

			//3D REFERENTIAL
			HideCursor();
			
			DrawGrid(20, 1.0f);        // Draw a grid
			DrawLine3D({ 0 }, { 0,10,0 }, DARKGRAY);
			DrawSphere({ 10,0,0 }, .2f, RED);
			DrawSphere({ 0,0,10 }, .2f, BLUE);
			DrawSphere({ 0,10,0 }, .2f, GREEN);
			//MyDrawDisk({ 0,0,0,0 }, { 0,0,0 }, 5, 20, BLUE)

			//Cylinder cylinder = { {0,0,0}, {0,2,0}, 2.f };
			//MyDrawCylinder(QuaternionIdentity(), cylinder, 28, true, RED);
			Quaternion qOrient = QuaternionFromAxisAngle(Vector3Normalize({ time*10,time*100,time*1000}), time);

			MyDrawDiskWire(qOrient, { 0,1,0 }, 5, 20, BLUE);
		}
		EndMode3D();

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------  
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
