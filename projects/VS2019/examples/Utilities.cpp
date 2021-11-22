#include "Utilities.h"
Vector3 GlobalToLocalVect(Vector3 vectGlobal, Referencial localRef) {
	Vector3 result;
	result.x = Vector3DotProduct(Vector3Subtract(localRef.origin, vectGlobal), localRef.i);
	result.y = Vector3DotProduct(Vector3Subtract(localRef.origin, vectGlobal), localRef.j);
	result.z = Vector3DotProduct(Vector3Subtract(localRef.origin, vectGlobal), localRef.k);
	return result;

}

Vector3 GlobalToLocalPos(Vector3 posGlobal, Referencial localRef) {
	Vector3 result;
	Vector3 O = { 0,0,0 };
	Vector3 Obis = Vector3Subtract(Vector3Subtract(localRef.origin, posGlobal), Vector3Subtract(O, localRef.origin));
	result.x = Vector3DotProduct(Vector3Subtract(Obis, posGlobal), localRef.i);
	result.y = Vector3DotProduct(Vector3Subtract(Obis, posGlobal), localRef.j);
	result.z = Vector3DotProduct(Vector3Subtract(Obis, posGlobal), localRef.k);
	return result;
}

Vector3 LocalToGlobalPos(Vector3 localPos, Referencial localRef) {
	Vector3 result;
	Vector3 O = { 0, 0, 0 };
	Vector3 OP = Vector3Add(Vector3Add(Vector3Scale(localRef.i, localPos.x), Vector3Scale(localRef.j, localPos.y)), Vector3Scale(localRef.k, localPos.z));
	return Vector3Add(Vector3Subtract(O, localRef.origin), OP);
}

Vector3 LocalToGlobalVec(Vector3 localVec, Referencial localRef) {
	return Vector3Add(Vector3Add(Vector3Scale(localRef.i, localVec.x),Vector3Scale(localRef.j,localVec.y)),Vector3Scale(localRef.k,localVec.z));

}