
#ifndef VECTOR4_H
#define VECTOR4_H

class Vector3;

class Vector4 {

private:

	float values[4];
	float mag;

	float calculateMag();

public:

	//Vector4 will make a copy of this array for itself
	Vector4(const float *newValues);
	Vector4(const Vector3 &vec, const float w);
	Vector4(const float x, const float y, const float z, const float w);
	~Vector4();

	//getter methods
	inline float x() const { return values[0]; }
	inline float y() const { return values[1]; }
	inline float z() const { return values[2]; }
	inline float w() const { return values[3];}
	inline float length() const { return mag; }

	//returns a normalizes version of this vector
	Vector4 normalize() const ;

	//operators
	Vector4 operator*(const float scalar) const;

	//adds two vectors
	Vector4 operator+(const Vector4 &other) const;

	Vector4 operator-(const Vector4 &other) const;

};

#endif