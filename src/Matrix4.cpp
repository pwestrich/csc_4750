
#include <cassert>

#include "Matrix4.h"
#include "Vector4.h"

Matrix4 Matrix4::identity(){

	static float matValues[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	static Matrix4 mat(matValues);
	return mat;

}

//the Matrix class will keep its own copy of this array
//there must be exactly 16 elements
Matrix4::Matrix4(const float *newVals){

	assert(newVals);

	for (int i = 0; i < 16; ++i){

		values[i] = newVals[i];

	}

}

Matrix4::~Matrix4(){}

//getter methods

//returns an element at index
float Matrix4::getValue(const int index) const {

	assert(index >= 0 && index < 16);
	
	return values[index];

}

//gets a value using its row-col location
float Matrix4::getValue(const int row, const int col) const {

	assert(row >= 0 && row < 4);
	assert(col >= 0 && col < 4);

	return index(row, col);

}

//will return a copy of its internal array
float *Matrix4::getValues() const {

	float *retMe = new float[16];

	for (int i = 0; i < 16; ++i){

		retMe[i] = values[i];

	}

	return retMe;

}

//operators

//multiplies a 4x4 matrix with a 1z4 vector
Vector4 Matrix4::operator*(const Vector4 &vec) const {

	float newVals[4];

	for (int i = 0; i < 4; ++i){

		newVals[i] = (values[index(i, 0)] * vec.x()) + (values[index(i, 1)] * vec.y()) + (values[index(i, 2)] * vec.z()) 
					+ (values[index(i, 3)] * vec.w());

	}

	return Vector4(newVals);

}

//multiplies two Matrix4s together
Matrix4 Matrix4::operator*(const Matrix4 &mat) const {

	float newVals[16];

	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 4; j++) {

			newVals[(4 * i) + j] = 0;
			for (int k = 0; k < 4; k++) {

			    newVals[(4 * i) + j] += values[(4 * i) + k] * mat[(4 * k) + j];

			}

		}

	}

	return Matrix4(newVals);

}

//returns a scaled matrix
Matrix4 Matrix4::operator*(const float scalar) const {

	float newVals[16];

	for (int i = 0; i < 16; ++i){

		newVals[i] = values[i] * scalar;

	}

	return Matrix4(newVals);

}

//adds two matricies together
Matrix4 Matrix4::operator+(const Matrix4 &other) const {

	float newVals[16];

	for (int i = 0; i < 16; ++i){

		newVals[i] = values[i] + other.getValue(i);

	}

	return Matrix4(newVals);

}

//adds a scalar to the whole matrix
Matrix4 Matrix4::operator+(const float scalar) const {

	float newVals[16];

	for (int i = 0; i < 16; ++i){

		newVals[i] = values[i] + scalar;

	}

	return Matrix4(newVals);

}

//subtracts two matricies
Matrix4 Matrix4::operator-(const Matrix4 &other) const {

	float newVals[16];

	for (int i = 0; i < 16; ++i){

		newVals[i] = values[i] - other.getValue(i);

	}

	return Matrix4(newVals);

}

//subtracts a scalar from the martix
Matrix4 Matrix4::operator-(const float scalar) const {

	float newVals[16];

	for (int i = 0; i < 16; ++i){

		newVals[i] = values[i] - scalar;

	}

	return Matrix4(newVals);

}

//returns the item at index
float Matrix4::operator[](const int index) const {

	assert(index >=0 && index < 16);
	return values[index];

}
