
#include <cassert>
#include <cmath>

#include "Vector3.h"
#include "Vector4.h"

//Vector4 will make a copy of this array for itself
Vector4::Vector4(const float *newValues) {

	assert(newValues);

	values[0] = newValues[0];
	values[1] = newValues[1];
	values[2] = newValues[2];
	values[3] = newValues[3];

}

Vector4::Vector4(const Vector3 &vec, const float w){

	values[0] = vec.x();
	values[1] = vec.y();
	values[2] = vec.z();
	values[3] = w;

}

Vector4::Vector4(const float x, const float y, const float z, const float w){

	values[0] = x;
	values[1] = y;
	values[2] = z;
	values[3] = w;

}

Vector4::~Vector4(){}

//returns a normalizes version of this vector
Vector4 Vector4::normalize() const {

	return Vector4(values[0] / mag, values[1] / mag, values[2] / mag, values[3] / mag);

}

//operators
Vector4 Vector4::operator*(const float scalar) const {

	float nx = values[0] * scalar;
	float ny = values[1] * scalar;
	float nz = values[2] * scalar;
	float nw = values[3] * scalar;

	return Vector4(nx, ny, nz, nw);

}

//adds two vectors
Vector4 Vector4::operator+(const Vector4 &other) const {

	float nx = values[0] + other.x();
	float ny = values[1] + other.y();
	float nz = values[2] + other.z();
	float nw = values[3] + other.w();

	return Vector4(nx, ny, nz, nw);

}

Vector4 Vector4::operator-(const Vector4 &other) const {

	float nx = values[0] - other.x();
	float ny = values[1] - other.y();
	float nz = values[2] - other.z();
	float nw = values[3] - other.w();

	return Vector4(nx, ny, nz, nw);

}

//private methods ---------------------------------------------------------------------------------

float Vector4::calculateMag(){

	float sum = (values[0] * values[0]) + (values[1] * values[1]) + (values[2] * values[2]) + (values[3] * values[3]);
	return sqrt(sum);

}
