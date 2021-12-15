#include "Utilities.h"
Vector3 GlobalToLocalVect(Vector3 vectGlobal, Referential localRef) {
	Vector3 result;
	result.x = Vector3DotProduct(localRef.origin, localRef.i);
	result.y = Vector3DotProduct(localRef.origin, localRef.j);
	result.z = Vector3DotProduct(localRef.origin, localRef.k);
	return result;

}

Vector3 GlobalToLocalPos(Vector3 posGlobal, Referential localRef) {
	Vector3 result;
	Vector3 O = { 0,0,0 };
	Vector3 Obis = Vector3Subtract(posGlobal, localRef.origin);
	result.x = Vector3DotProduct(Obis, localRef.i);
	result.y = Vector3DotProduct(Obis, localRef.j);
	result.z = Vector3DotProduct(Obis, localRef.k);
	return result;
}

Vector3 LocalToGlobalPos(Vector3 localPos, Referential localRef) {
	Vector3 result;
	Vector3 O = { 0, 0, 0 };
	Vector3 OP = Vector3Add(Vector3Add(Vector3Scale(localRef.i, localPos.x), Vector3Scale(localRef.j, localPos.y)), Vector3Scale(localRef.k, localPos.z));
	return Vector3Add(Vector3Subtract(O, localRef.origin), OP);
}

Vector3 LocalToGlobalVect(Vector3 localVec, Referential localRef) {
	return Vector3Add(
				Vector3Add(
					Vector3Scale(localRef.i, localVec.x),Vector3Scale(localRef.j,localVec.y)
				),
			Vector3Scale(localRef.k,localVec.z));

}

Referential ReferentialByQuarternion(Referential r, Quaternion q) {
	Vector3 i2 = Vector3RotateByQuaternion(r.i, q);
	Vector3 j2 = Vector3RotateByQuaternion(r.j, q);
	Vector3 k2 = Vector3RotateByQuaternion(r.k, q);
	Referential r2 = { r.origin,i2,j2,k2, QuaternionMultiply( r.quat,q) };
	return r2;
}

Referential changeReferential(Referential ref, Vector3 translation, Quaternion rotation) {
	Referential rResult = { Vector3Add(ref.origin,translation),ref.i, ref.j, ref.k, ref.quat };
	rResult = ReferentialByQuarternion(rResult, rotation);
	return rResult;
}
