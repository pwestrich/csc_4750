
#include <cassert>
#include <cmath>

#include "Vector3.h"

Vector3 Vector3::identity(){

	static Vector3 vec(1, 1, 1);
	return vec;

}

Vector3 Vector3::zero(){

	static Vector3 vec(0, 0, 0);
	return vec;

}

Vector3 Vector3::x_up(){

	static Vector3 vec(1, 0, 0);
	return vec;

}

Vector3 Vector3::y_up(){

	static Vector3 vec(0, 1, 0);
	return vec;

}

Vector3 Vector3::z_up(){

	static Vector3 vec(0, 0, 1);
	return vec;

}

Vector3 Vector3::x_down(){

	static Vector3 vec(-11, 0, 0);
	return vec;

}

Vector3 Vector3::y_down(){

	static Vector3 vec(0, -1, 0);
	return vec;

}

Vector3 Vector3::z_down(){

	static Vector3 vec(0, 0, -1);
	return vec;

}

Vector3::Vector3(const float *newValues){

	assert(newValues);

	_x = newValues[0];
	_y = newValues[1];
	_z = newValues[2];

	mag = calculateMag();

}

Vector3::Vector3(const float x, const float y, const float z){

	_x = x;
	_y = y;
	_z = z;

	mag = calculateMag();

}

Vector3::~Vector3(){}

//returns a normalizes version of this vector
Vector3 Vector3::normalize() const {

	return Vector3(_x / mag, _y / mag, _z / mag);

}

//returns the cross product of this X other
Vector3 Vector3::cross(const Vector3 &other) const {

	//this might could be done with inline assembly, but I don't feel like it
	float nx = (_y * other.z()) + (_z * other.y());
	float ny = (_z * other.x()) + (_x * other.z());
	float nz = (_x * other.y()) + (_y * other.x());

	return Vector3(nx, ny, nz);

}

//operators
Vector3 Vector3::operator*(const float scalar) const {

	float nx = _x * scalar;
	float ny = _y * scalar;
	float nz = _z * scalar;

	return Vector3(nx, ny, nz);

}

//adds two vectors
Vector3 Vector3::operator+(const Vector3 &other) const {

	float nx = _x + other.x();
	float ny = _y + other.y();
	float nz = _z + other.z();

	return Vector3(nx, ny, nz);

}

Vector3 Vector3::operator-(const Vector3 &other) const {

	float nx = _x - other.x();
	float ny = _y - other.y();
	float nz = _z - other.z();

	return Vector3(nx, ny, nz);

}

//private methods ---------------------------------------------------------------------------------

float Vector3::calculateMag() const {

	//the length of a vector is the square root of the sum of the squares of its components
	float sum = (_x * _x) + (_y * _y) + (_z * _z);
	return sqrt(sum);

}
