
#ifndef MATRIX3_H
#define MATRIX3_H

class Vector3;
class Matrix3;

//the identity matrix
extern const Matrix3 IDENTITY;

class Matrix3 {

private:

	float values[9];

	inline float index(const int row, const int col) const {

		return ((col * 3) + row);

	}

public:

	//the Matrix class will keep its own copy of this array
	//there must be exactly nine elements
	Matrix3(const float *newVals);
	~Matrix3();

	//getter methods

	//returns an element at index
	float getValue(const int index) const;

	//gets a value using its row-col location
	float getValue(const int row, const int col) const;

	//will return a copy of its internal array
	float *getValues() const;

	//operators

	//multiplies a 3x3 matrix with a 1z3 vector
	Vector3 operator*(const Vector3 &vec) const;

	//multiplies two Matrix3s together
	Matrix3 operator*(const Matrix3 &mat) const;

	//returns a scaled matrix
	Matrix3 operator*(const float scalar) const;

	//adds two matricies together
	Matrix3 operator+(const Matrix3 &other) const;

	//adds a scalar to the whole matrix
	Matrix3 operator+(const float scalar) const;

	//returns the item at index
	float operator[](const int index) const;

};

#endif
