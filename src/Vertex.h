
#ifndef VERTEX_H
#define VERTEX_H

#include "Vector4.h"

class Vertex {

private:

	Vector4 location;

public:

	Vertex(const float x, const float y, const float z, const float w) : location(x, y, z, w){}
	Vertex(const Vector4 &vec) : location(vec){}

	~Vertex();

	inline Vector4 vector() const { return location;}
	inline float x() const { return location.x();}
	inline float y() const { return location.y();}
	inline float z() const { return location.z();}
	inline float w() const { return location.w();}

};

#endif
