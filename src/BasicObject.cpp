
#include <iostream>
#include <fstream>
#include <string>

#include "utilities.h"
#include "BasicObject.h"
#include "Matrix4.h"
#include "Vector4.h"
#include "Vertex.h"
#include "Face.h"
#include "Texture.h"

//reads in an object from a .obj file
BasicObject::BasicObject(const std::string &filename, const float _shininess){

	shininess = _shininess;

	std::ifstream inFile(filename);
	std::string line;
	int texCount = 0;
	int faceCount = 0;

	if (!inFile){

		cerr << "Error opening file: " << filename << endl;
		exit(EXIT_FAILURE);

	}

	getline(inFile, line, '\n');

	while (!inFile.eof()){

		if (line.find("#") == 0){

			goto next_line; //ignore comments

		/*} else if (line.find("mtllib") == 0) {

			goto next_line; //ignore material info

		} else if (line.find("o") == 0){

			goto next_line; //ignore object names

		} else if (line.find("vn") == 0){

			goto next_line; //ignore normals

		} else if (line.find("g") == 0){

			goto next_line; //ignore this line

		} else if (line.find("usemtl") == 0){

			goto next_line; //no materials

		} else if (line.find("end") == 0){

			goto next_line; //end of file marker*/

		} else if (line.find("vt") == 0){

			//texture line
			TextureCoordinates coords;

			std::vector<std::string> tokens = split(line, ' ');

			coords.s1 = stof(tokens[1]);
			coords.t1 = stof(tokens[2]);

			coords.s2 = stof(tokens[3]);
			coords.t2 = stof(tokens[4]);

			coords.s3 = stof(tokens[5]);
			coords.t3 = stof(tokens[6]);

			faces[faceCount]->addTextureCoordinates(coords);

			++texCount;

			if (texCount == 2){

				++faceCount;
				texCount = 0;

			}

		} else if (line.find("v") == 0){

			//this is a vertex
			std::vector<std::string> tokens = split(line, ' ');

			float x = stof(tokens[1]);
			float y = stof(tokens[2]);
			float z = stof(tokens[3]);

			points.push_back(new Vertex(Vector4(x, y, z, 1.0)));

		} else if (line.find("f") == 0){

			//this is a face definition
			std::vector<std::string> tokens = split(line, ' ');

			int one   = stoi(tokens[1]);
			int two   = stoi(tokens[2]);
			int three = stoi(tokens[3]);

			faces.push_back(new Face(points[one - 1], points[two - 1], points[three - 1]));

			//add this face to each vertex
			points[one   - 1]->addFace(faces.back());
			points[two   - 1]->addFace(faces.back());
			points[three - 1]->addFace(faces.back());

		}

		next_line: getline(inFile, line, '\n');

	}

}

//draws the object
void BasicObject::render(const Matrix4 &transform, const Matrix4 &windowingMatrix, const Vector4 &eyepoint, const Vector4 &material, 
						 const Light &ambient, const Light &point, const Texture &tex, const float attenuation) const {

	//tell each face to render itself
	for (size_t i = 0; i < faces.size(); ++i){

		faces[i]->render(transform, windowingMatrix, eyepoint, material, ambient, point, tex, attenuation, shininess);

	}

}
