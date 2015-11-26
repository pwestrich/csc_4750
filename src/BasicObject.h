
#ifndef BASIC_OBJECT_H
#define BASIC_OBJECT_H

#include <cstdint>
#include <string>
#include <vector>

class Matrix4;
class Texture;

class BasicObject {

private:

	float *texCoords;
	float *verticies;
	float *normals;
	uint32_t *faces;

	int _numVerticies;
	int _numFaces;
	int _indexCount;

	float shininess;

public:

	//reads in an object from a .obj file
	BasicObject(const std::string &filename, const float shininess);

	~BasicObject();

	//draws the object
	void render(const Matrix4 &transform, const Texture &tex, const Texture &bumpMap) const;

};

#endif
