
#ifndef BASIC_OBJECT_H
#define BASIC_OBJECT_H

#include <string>
#include <vector>

class Matrix4;
class Vertex;
class Face;

class BasicObject {

private:

	//every point that makes up this object
	std::vector<Vertex*> points;

	//every face that amkes up this object
	std::vector<Face*> faces;

public:

	//reads in an object from a .obj file
	BasicObject(const std::string &filename);

	//deallocates the memory for the entire object
	~BasicObject();

	//draws the object
	void render(const Matrix4 &transform);

};

#endif
