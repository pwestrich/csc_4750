
#include <cassert>

#include "Matrix3.h"
#include "Vector3.h"

Matrix3 Matrix3::identity(){

	static float matValues[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
	static Matrix3 mat(matValues);
	return mat;

}

//the Matrix class will keep its own copy of this array
//there must be exactly nine elements
Matrix3::Matrix3(const float *newVals){

	assert(newVals);

	//hopefilly the compiler will unroll this for me
	for (int i = 0; i < 9; ++i){

		values[i] = newVals[i];

	}

}

Matrix3::~Matrix3(){}

//getter methods

//returns an element at index
float Matrix3::getValue(const int index) const {

	assert(index >= 0 && index < 9);

	return values[index];

}

//gets a value using its row-col location
float Matrix3::getValue(const int row, const int col) const {

	assert(row >= 0 && row < 3);
	assert(col >= 0 && col < 3);

	return index(row, col);

}

//will return a copy of its internal array
float *Matrix3::getValues() const {

	float *retMe = new float[9];

	for (int i = 0; i < 9; ++i){

		retMe[i] = values[i];

	}

	return retMe;

}

//operators

//multiplies a 3x3 matrix with a 1z3 vector
Vector3 Matrix3::operator*(const Vector3 &vec) const {

	float nx = (values[0] * vec.x()) + (values[1] * vec.y()) + (values[2] * vec.z());
	float ny = (values[3] * vec.x()) + (values[4] * vec.y()) + (values[5] * vec.z());
	float nz = (values[6] * vec.x()) + (values[7] * vec.y()) + (values[8] * vec.z());

	return Vector3(nx, ny, nz);

}

//multiplies two Matrix3s together
Matrix3 Matrix3::operator*(const Matrix3 &mat) const {

	float newVals[9];

	newVals[0] = (values[0] * mat[0]) + (values[1] * mat[3]) + (values[2] * mat[6]);
	newVals[1] = (values[0] * mat[1]) + (values[1] * mat[4]) + (values[2] * mat[7]);
	newVals[2] = (values[0] * mat[2]) + (values[1] * mat[5]) + (values[2] * mat[8]);

	newVals[3] = (values[3] * mat[0]) + (values[4] * mat[3]) + (values[5] * mat[6]);
	newVals[4] = (values[3] * mat[1]) + (values[4] * mat[4]) + (values[5] * mat[7]);
	newVals[5] = (values[3] * mat[2]) + (values[4] * mat[5]) + (values[5] * mat[8]);

	newVals[6] = (values[6] * mat[0]) + (values[7] * mat[3]) + (values[8] * mat[6]);
	newVals[7] = (values[6] * mat[1]) + (values[7] * mat[4]) + (values[8] * mat[7]);
	newVals[8] = (values[6] * mat[2]) + (values[7] * mat[5]) + (values[8] * mat[8]);

	return Matrix3(newVals);

}

//returns a scaled matrix
Matrix3 Matrix3::operator*(const float scalar) const {

	float newVals[9];

	for (int i = 0; i < 9; ++i){

		newVals[i] = values[i] * scalar;

	}

	return Matrix3(newVals);

}

//adds two matricies together
Matrix3 Matrix3::operator+(const Matrix3 &other) const {

	float newVals[9];

	for (int i = 0; i < 9; ++i){

		newVals[i] = values[i] + other[i];

	}

	return Matrix3(newVals);

}

//adds a scalar to the whole matrix
Matrix3 Matrix3::operator+(const float scalar) const {

	float newVals[9];

	for (int i = 0; i < 9; ++i){

		newVals[i] = values[i] + scalar;

	}

	return Matrix3(newVals);

}

//subtracts two matricies
Matrix3 Matrix3::operator-(const Matrix3 &other) const {

	float newVals[9];

	for (int i = 0; i < 9; ++i){

		newVals[i] = values[i] - other[i];

	}

	return Matrix3(newVals);

}

//subtracts a scalar from the martix
Matrix3 Matrix3::operator-(const float scalar) const {

	float newVals[9];

	for (int i = 0; i < 9; ++i){

		newVals[i] = values[i] - scalar;

	}

	return Matrix3(newVals);

}

//returns the item at index
float Matrix3::operator[](const int index) const {

	assert(index >=0 && index < 9);

	return values[index];

}
