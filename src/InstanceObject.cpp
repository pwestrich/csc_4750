
#include <fstream>
#include <iostream>
#include <vector>

#include "InstanceObject.h"
#include "BasicObject.h"
#include "Matrix4.h"
#include "AffineTransformations.h"

InstanceObject::InstanceObject(std::shared_ptr<BasicObject> obj, const std::string &filename) : InstanceObject(obj, Matrix4::identity()){

	std::ifstream inFile(filename);

	if (!inFile){

		std::cerr << "Invalid filename: " << filename << std::endl;
		exit(EXIT_FAILURE);

	}

	std::string buffer;
	std::vector<std::string> lines;

	do {

		getline(inFile, buffer);
		lines.push_back(buffer);

	} while (!inFile.eof());

	if (lines.size() != 13){

		std::cerr << "Error: File invalid: " << filename << std::endl;
		exit(EXIT_FAILURE);

	}

	//lines 1, 2, 3 have the scale in x, y, and z
	float xs = stof(lines[1]);
	float ys = stof(lines[2]);
	float zs = stof(lines[3]);

	//lines 5, 6, 7, have the rotations in x, y, and z
	float xr = stof(lines[5]);
	float yr = stof(lines[6]);
	float zr = stof(lines[7]);

	//lines 9, 10, 11 have the translate in x, y, and z
	float xt = stof(lines[9]);
	float yt = stof(lines[10]);
	float zt = stof(lines[11]);

	//create the transform matricies
	Matrix4 T = createTranslateMatrix(xt, yt, zt);
	Matrix4 RX = createRotationMatrixX(xr);
	Matrix4 RY = createRotationMatrixY(yr);
	Matrix4 RZ = createRotationMatrixZ(zr);
	Matrix4 S = createScaleMatrix(xs, ys, zs);

	Matrix4 transform = T * RX * RY * RZ * S;

	buildTransform(transform);

}

//used to build up several transforms
void InstanceObject::buildTransform(const Matrix4 &newTransform){

	//take the incoming matrix, and multiply the current transform by it
	instanceTransform = newTransform * instanceTransform;

}

//renders the object using the current instance transform
void InstanceObject::render(const Matrix4 &transform) const {

	//tell the BasicObject to render with the instance transform
	parent->render(transform * instanceTransform);

}
