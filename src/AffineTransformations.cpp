
//for math constants, like pi
#define _USE_MATH_DEFINES

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

	float values[16] = {1, 0, 0, tx, 0, 1, 0, ty, 0, 0, 1, tz, 0, 0, 0, 1};
	return Matrix4(values);

}

//creates the rotation matrix given an axis and angle (in degrees) to rotate about
Matrix4 createRotationMatrix(const float rx, const float ry, const float rz, const float rw){

	//first, I'll need the degree measurement in radians, as well as its (co)sine
	const float angle  = (M_PI * rw) / 180.0;
	const float cosine = cos(angle);
	const float sine   = sin(angle);

	//and a few more values
	const float xSq	 = rx * rx;
	const float ySq  = ry * ry;
	const float zSq	 = rz * rz;
	const float cos1 = 1.0 - cosine;

	//if you concatinate the various matricies together, it loks like this:
	float values[16];

	//row 1
	values[0] = cosine + (xSq * cos1);
	values[1] = (rx * ry * cos1) - (rz * cosine);
	values[2] = (rx * rz * cos1) + (ry * sine);
	values[3] = 0.0;

	//row 2
	values[4] = (ry * rx * cos1) + (rz * sine);
	values[5] = cosine + (ySq * cos1);
	values[6] = (ry * rz * cos1) - (rx * sine);
	values[7] = 0.0;

	//row 3
	values[8] = (rz * rx * cos1) - (ry * sine);
	values[9] = (ry * rx * cos1) + (rx * sine);
	values[10] = cosine + (zSq * cos1);
	values[11] = 0.0;

	//this one is easy
	values[12] = values[13] = values[14] = 0.0;
	values[15] = 1.0;

	return Matrix4(values);

}

//these are for treating rotations about each axis seperatley
Matrix4 createRotationMatrixX(const float degrees){

	//first, crunch some numbers
	const float radians = (M_PI * degrees) / 180.0;
	const float cosine = cos(radians);
	const float sine = sin(radians);

	//then create the matrix
	float values[16] = {1, 0	 , 0     , 0,
						0, cosine, -sine , 0,
						0, sine  , cosine, 0,
						0, 0	 , 0     , 1};

	return Matrix4(values);

}

Matrix4 createRotationMatrixY(const float degrees){

	//first, crunch some numbers
	const float radians = (M_PI * degrees) / 180.0;
	const float cosine = cos(radians);
	const float sine = sin(radians);

	//then create the matrix
	float values[16] = {cosine, 0, sine  , 0,
						0	  , 1, 0	 , 0,
						-sine , 0, cosine, 0,
						0	  , 0, 0	 , 1};

	return Matrix4(values);

}

Matrix4 createRotationMatrixZ(const float degrees){

	//first, crunch some numbers
	const float radians = (M_PI * degrees) / 180.0;
	const float cosine = cos(radians);
	const float sine = sin(radians);

	//then create the matrix
	float values[16] = {cosine, -sine , 0, 0,
						sine  , cosine, 0, 0,
						0	  , 0	  , 1, 0,
						0	  , 0	  , 0, 1};

	return Matrix4(values);

}
