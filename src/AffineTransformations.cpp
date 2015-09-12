
#include <cmath>

#include "AffineTransformations.h"
#include "Vector4.h"
#include "Matrix4.h"

//creates the scale matrix out of the scale in x, y, and z directions
//(0, 1) for shrinking, (1, inf) for growing, and 1 for no change
Matrix4 createScaleMatrix(const float sx, const float sy, const float sz){

	float values[16] = {sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1};
	return Matrix4(values);

}

//creates the translation matrix given the translation in each direction
Matrix4 createTranslateMatrix(const float tx, const float ty, const float tz){

	float values[16] = {0, 0, 0, tx, 0, 0, 0, ty, 0, 0, 0, tz, 0, 0, 0, 1};
	return Matrix4(values);

}

//creates the rotation matrix given an axis and angle to rotate about
Matrix4 createRotationMatrix(const float rx, const float ry, const float rz, const float rw){

	return Matrix4::identity();

}
