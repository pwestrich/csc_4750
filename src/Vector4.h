
#ifndef VECTOR4_H
#define VECTOR4_H

#include <iostream>

class Vector4 {

private:

	float values[4];
	float mag;

	float calculateMag() const;

public:

	static Vector4 identity();
	static Vector4 zero();
	static Vector4 x_up();
	static Vector4 y_up();
	static Vector4 z_up();
	static Vector4 w_up();
	static Vector4 x_down();
	static Vector4 y_down();
	static Vector4 z_down();
	static Vector4 w_down();

	//Vector4 will make a copy of this array for itself
	Vector4(const float *newValues);
	Vector4(const float x, const float y, const float z, const float w);

	//getter methods
	inline float x() const { return values[0];}
	inline float y() const { return values[1];}
	inline float z() const { return values[2];}
	inline float w() const { return values[3];}
	inline float length() const { return mag;}

	//returns the dot product of two vectors
	float dot(const Vector4 &other) const;

	//returns the cross product of two vectors
	Vector4 cross(const Vector4 &other) const;

	//returns a normalizes version of this vector
	Vector4 normalize() const;

	//homogenizes the vector
	Vector4 homogenize() const;

	//operators

	friend std::ostream& operator<<(std::ostream &out, const Vector4 &vec);

	Vector4 operator*(const float scalar) const;

	//adds two vectors
	Vector4 operator+(const Vector4 &other) const;

	Vector4 operator-(const Vector4 &other) const;

	float operator[](const int index) const;

};

#endif
