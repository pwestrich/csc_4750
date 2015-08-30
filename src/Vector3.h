
#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3 {

private:

	float _x;
	float _y;
	float _z;
	float mag;

	float calculateMag();

public:

	static Vector3 identity();
	static Vector3 zero();
	static Vector3 x_up();
	static Vector3 y_up();
	static Vector3 z_up();
	static Vector3 x_down();
	static Vector3 y_down();
	static Vector3 z_down();

	//Vector3 will make its own copy of this array
	Vector3(const float *newValues);
	Vector3(const float x, const float y, const float z);
	~Vector3();

	//getter methods
	inline float x() const { return _x; }
	inline float y() const { return _y; }
	inline float z() const { return _z; }
	inline float length() const { return mag; }

	//returns a normalizes version of this vector
	Vector3 normalize() const;

	//returns the cross product of this X other
	Vector3 cross(const Vector3 &other) const;

	//operators
	Vector3 operator*(const float scalar) const;

	//adds two vectors
	Vector3 operator+(const Vector3 &other) const;

	Vector3 operator-(const Vector3 &other) const;

};

#endif
