
#include <cassert>
#include <cmath>

#include "Vector4.h"

Vector4 Vector4::identity(){

	static Vector4 vec(1, 1, 1, 1);
	return vec;

}

Vector4 Vector4::zero(){

	static Vector4 vec(0, 0, 0, 0);
	return vec;

}

Vector4 Vector4::x_up(){

	static Vector4 vec(1, 0, 0, 0);
	return vec;

}

Vector4 Vector4::y_up(){

	static Vector4 vec(0, 1, 0, 0);
	return vec;

}

Vector4 Vector4::z_up(){

	static Vector4 vec(0, 0, 1, 0);
	return vec;

}

Vector4 Vector4::w_up(){

	static Vector4 vec(0, 0, 0, 1);
	return vec;

}

Vector4 Vector4::x_down(){

	static Vector4 vec(-1, 0, 0, 0);
	return vec;

}

Vector4 Vector4::y_down(){

	static Vector4 vec(0, -1, 0, 0);
	return vec;

}

Vector4 Vector4::z_down(){

	static Vector4 vec(0, 0, -1, 0);
	return vec;

}

Vector4 Vector4::w_down(){

	static Vector4 vec(0, 0, 0, -1);
	return vec;

}

//Vector4 will make a copy of this array for itself
Vector4::Vector4(const float *newValues) {

	assert(newValues);

	values[0] = newValues[0];
	values[1] = newValues[1];
	values[2] = newValues[2];
	values[3] = newValues[3];

	mag = calculateMag();

}

Vector4::Vector4(const float x, const float y, const float z, const float w){

	values[0] = x;
	values[1] = y;
	values[2] = z;
	values[3] = w;

	mag = calculateMag();

}

float Vector4::dot(const Vector4 &other) const {

	return (x() * other.x()) + (y() * other.y()) + (z() * other.z());

}

//returns the cross product of two vectors
Vector4 Vector4::cross(const Vector4 &other) const {

	//only vectors can be crossed
	assert(w() == 0.0 && other.w() == 0.0);

	float nx = (y() * other.z()) - (z() * other.y());
	float ny = (z() * other.x()) - (x() * other.z());
	float nz = (x() * other.y()) - (y() * other.x());

	return Vector4(nx, ny, nz, 0.0);

}

//returns a normalizes version of this vector
Vector4 Vector4::normalize() const {

	//only vectors can be normalized
	assert(w() == 0.0);

	if (mag == 1.0) return Vector4(values);

	float denom = 1.0 / mag;

	return Vector4(values[0] * denom, values[1] * denom, values[2] * denom, 0.0);

}

//homogenizes the vector
Vector4 Vector4::homogenize() const {

	//only points can be homogenized
	assert(values[3] != 0.0);

	float nx = values[0] / values[3];
	float ny = values[1] / values[3];
	float nz = values[2] / values[3];

	return Vector4(nx, ny, nz, 1.0);

}

//operators
Vector4 Vector4::operator*(const float scalar) const {

	//only vectors can be scaled
	assert(w() == 0.0);

	float nx = values[0] * scalar;
	float ny = values[1] * scalar;
	float nz = values[2] * scalar;

	return Vector4(nx, ny, nz, 0.0);

}

//adds two vectors
Vector4 Vector4::operator+(const Vector4 &other) const {

	//only vectors can be added together
	assert(other.w() == 0.0 && w() == 0.0);

	float nx = values[0] + other.x();
	float ny = values[1] + other.y();
	float nz = values[2] + other.z();

	return Vector4(nx, ny, nz, 0.0);

}

Vector4 Vector4::operator-(const Vector4 &other) const {

	float nx = values[0] - other.x();
	float ny = values[1] - other.y();
	float nz = values[2] - other.z();
	float nw = values[3] - other.w();

	return Vector4(nx, ny, nz, nw);

}

float Vector4::operator[](const int index) const {

	assert(index >= 0 && index < 4);
	return values[index];

}

//private methods ---------------------------------------------------------------------------------

float Vector4::calculateMag() const {

	float sum = (values[0] * values[0]) + (values[1] * values[1]) + (values[2] * values[2]);
	return sqrt(sum);

}
