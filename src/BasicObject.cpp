
#include <iostream>
#include <fstream>
#include <string>

#include "utilities.h"
#include "BasicObject.h"
#include "Matrix4.h"
#include "Face.h"
#include "Vertex.h"

//reads in an object from a .obj file
BasicObject::BasicObject(const std::string &filename){

	std::ifstream inFile(filename);
	std::string line;

	if (!inFile){

		cerr << "Error opening file: " << filename << endl;
		exit(EXIT_FAILURE);

	}

	getline(inFile, line, '\n');

	while (!inFile.eof()){

		if (line.find("#") == 0){

			goto next_line; //ignore comments

		} else if (line.find("mtllib") == 0) {

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

			goto next_line; //end of file marker

		} else if (line.find("v") == 0){

			//this is a vertex
			std::vector<std::string> tokens = split(line, ' ');

			float x = atof(tokens[1].c_str());
			float y = atof(tokens[2].c_str());
			float z = atof(tokens[3].c_str());

			points.push_back(new Vertex(x, y, z, 1.0));

		} else if (line.find("f") == 0){

			//this is a face definition
			std::vector<std::string> tokens = split(line, ' ');

			int one = atoi(tokens[1].c_str());
			int two = atoi(tokens[2].c_str());
			int three = atoi(tokens[3].c_str());

			faces.push_back(new Face(points[one - 1], points[two - 1], points[three - 1]));

		}

		next_line: getline(inFile, line, '\n');

	}

}

//draws the object
void BasicObject::render(const Matrix4 &transform) const {

	//tell each face to render itself
	for (size_t i = 0; i < faces.size(); ++i){

		faces[i]->render(transform);

	}

}
