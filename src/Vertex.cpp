
#include <cassert>

#include "Vertex.h"
#include "Matrix4.h"
#include "Face.h"

//add a face to the list of faces that this vertex is a part of
void Vertex::addFace(Face *const face){

	assert(face);

	faces.push_back(face);

}

//get the average normal from all faces that this vertex is a member of
Vector4 Vertex::averageNormal(const Matrix4 &transform) const {

	Vector4 normal = Vector4::zero();

	for (size_t i = 0; i < faces.size(); ++i){

		normal = normal + faces[i]->getNormal(transform);

	}

	normal = normal / faces.size();

	return normal.normalize();

}
