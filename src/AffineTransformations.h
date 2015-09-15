
#ifndef AFFINE_TRANSFORMATIONS_H
#define AFFINE_TRANSFORMATIONS_H

#include "Vector4.h"
#include "Matrix4.h"

//creates the scale matrix out of the scale in x, y, and z directions
//(0, 1) for shrinking, (1, inf) for growing, and 1 for no change
Matrix4 createScaleMatrix(const float sx, const float sy, const float sz);

//creates the translation matrix given the translation in each direction
Matrix4 createTranslateMatrix(const float tx, const float ty, const float tz);

//creates the rotation matrix given an axis and angle (in degrees) to rotate about
Matrix4 createRotationMatrix(const float rx, const float ry, const float rz, const float rw);

//these are for treating rotations about each axis seperatley
Matrix4 createRotationMatrixX(const float degrees);
Matrix4 createRotationMatrixY(const float degrees);
Matrix4 createRotationMatrixZ(const float degrees);

//these methods are overloads for using vectors to specify the transformations
inline Matrix4 createScaleMatrix(const Vector4 &scale){

	return createScaleMatrix(scale.x(), scale.y(), scale.z());

}

inline Matrix4 createTranslateMatrix(const Vector4 &translate){

	return createTranslateMatrix(translate.x(), translate.y(), translate.z());

}

inline Matrix4 createRotationMatrix(const Vector4 &rotation){

	return createRotationMatrix(rotation.x(), rotation.y(), rotation.z(), rotation.w());

}

#endif
