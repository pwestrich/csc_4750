
#ifndef BASIC_OBJECT_H
#define BASIC_OBJECT_H

#include <string>
#include <vector>

class Matrix4;
class Vector4;
class Face;

class BasicObject {

private:

	//every point that makes up this object
	std::vector<Vector4*> points;

	//every face that amkes up this object
	std::vector<Face*> faces;

	float shininess;

public:

	//reads in an object from a .obj file
	BasicObject(const std::string &filename, const float shininess);

	//draws the object
	void render(const Matrix4 &transform, const Matrix4 &windowingMatrix, const Vector4 &eyepoint, const Vector4 &material, const float attenuation) const;

};

#endif
