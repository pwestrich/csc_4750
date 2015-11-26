
#include <fstream>
#include <iostream>
#include <vector>

#include "InstanceObject.h"
#include "BasicObject.h"
#include "Matrix4.h"
#include "AffineTransformations.h"

InstanceObject::InstanceObject(const BasicObject *obj, const std::string &filename, const std::string &texFilename, 
				        	   const std::string &bumpMapFilename, const int tw, const int th, const int bw, const int bh) 
							  : InstanceObject(obj, Matrix4::identity(), texFilename, bumpMapFilename, tw, th, bw, bh){

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

	if (lines.size() < 13){

		std::cerr << "Error: File invalid: " << filename << std::endl;
		exit(EXIT_FAILURE);

	}

	//lines 1, 2, 3 have the scale in x, y, and z
	const float xs = stof(lines[1]);
	const float ys = stof(lines[2]);
	const float zs = stof(lines[3]);

	//lines 5, 6, 7, have the rotations in x, y, and z
	const float xr = stof(lines[5]);
	const float yr = stof(lines[6]);
	const float zr = stof(lines[7]);

	//lines 9, 10, 11 have the translate in x, y, and z
	const float xt = stof(lines[9]);
	const float yt = stof(lines[10]);
	const float zt = stof(lines[11]);

	//lines 13, 14, 15 are the material color
	const float r = stof(lines[13]);
	const float g = stof(lines[14]);
	const float b = stof(lines[15]);

	inFile.close();

	//create the transform matricies
	Matrix4 T = createTranslateMatrix(xt, yt, zt);
	Matrix4 RX = createRotationMatrixX(xr);
	Matrix4 RY = createRotationMatrixY(yr);
	Matrix4 RZ = createRotationMatrixZ(zr);
	Matrix4 S = createScaleMatrix(xs, ys, zs);

	instanceTransform = T * RX * RY * RZ * S;

	material = Vector4(r, g, b, 1.0);

}

//used to build up several transforms
void InstanceObject::buildTransform(const Matrix4 &newTransform){

	//take the incoming matrix, and multiply the current transform by it
	instanceTransform = newTransform * instanceTransform;

}

//renders the object using the current instance transform
void InstanceObject::render(const Matrix4 &transform) const {

	//tell the BasicObject to render with the instance transform
	parent->render(transform * instanceTransform, tex, bumpMap);

}
