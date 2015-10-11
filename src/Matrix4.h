
#ifndef MATRIX4_H
#define MATRIX4_H

#include <iostream>

class Vector4;

class Matrix4 {

private:

	float values[16];

	inline int index(const int row, const int col) const {

		return ((col * 4) + row);

	}

public:

	static Matrix4 identity();

	Matrix4();

	//the Matrix class will keep its own copy of this array
	//there must be exactly 16 elements
	Matrix4(const float *newVals);
	~Matrix4();

	//getter methods

	//returns an element at index
	float getValue(const int index) const;

	//gets a value using its row-col location
	float getValue(const int row, const int col) const;

	//will return a copy of its internal array
	float *getValues() const;

	//operators

	friend std::ostream &operator<<(std::ostream &out, const Matrix4 &mat);

	//multiplies a 4x4 matrix with a 1z4 vector
	Vector4 operator*(const Vector4 &vec) const;

	//multiplies two Matrix4s together
	Matrix4 operator*(const Matrix4 &mat) const;

	//returns a scaled matrix
	Matrix4 operator*(const float scalar) const;

	//adds two matricies together
	Matrix4 operator+(const Matrix4 &other) const;

	//adds a scalar to the whole matrix
	Matrix4 operator+(const float scalar) const;

	//subtracts two matricies
	Matrix4 operator-(const Matrix4 &other) const;

	//subtracts a scalar from the martix
	Matrix4 operator-(const float scalar) const;

	//returns the item at index
	float operator[](const int index) const;

};

#endif
