
#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3.h"

class Vertex {

private:

	Vector3 location;

public:

	Vertex(const float x, const float y, const float z) : location(x, y, z){}
	Vertex(const Vector3 &vec) : location(vec){}

	~Vertex();

	inline float x() const { return location.x();}
	inline float y() const { return location.y();}
	inline float z() const { return location.z();}

};

#endif
