
#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

#include "Vector4.h"

class Face;
class Matrix4;

class Vertex {

private:

	//the point this vertex holds
	Vector4 point;

	//the faces this vertex is a member of
	std::vector<Face*> faces;

public:

	//construct a vertex with either a vector or floats
	Vertex(const Vector4 &vec) : point(vec){}
	Vertex(const float x, const float y, const float z, const float w = 1.0) : point(x, y, z, w){}

	//get a copy of the underlying vector
	inline Vector4 vector() const { return point;}

	//add a face to the list of faces that this vertex is a part of
	void addFace(Face *const face);

	//get the average normal from all faces that this vertex is a member of
	Vector4 averageNormal(const Matrix4 &transform) const;

};

#endif
