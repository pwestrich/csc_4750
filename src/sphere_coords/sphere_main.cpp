
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//borrow some things from the program
#include "../Vector4.h"
#include "../utilities.h"

struct Face {

	Vector4 *one;
	Vector4 *two;
	Vector4 *three;

	Face(Vector4 *_one, Vector4 *_two, Vector4 *_three) : one(_one), two(_two), three(_three){}

};

void readFile(std::ifstream &inFile, std::vector<Vector4*> &points, std::vector<Face*> &faces); 

[[noreturn]] inline void usage(const char *name){

	std::cout << "Usage: " << name << " <input_file> <output_file>" << std::endl;
	exit(EXIT_FAILURE);

}

int main(const int argc, const char **argv){

	//check argument count
	if (argc < 2){

		std::cerr << "Error: Too few arguments." << std::endl;
		usage(argv[0]);

	}

	//open files to be read/written
	std::ifstream inFile(argv[1]);
	std::ofstream outFile(argv[2]);

	if (!inFile){

		std::cerr << "Invalid input file: " << argv[1] << std::endl;
		return EXIT_FAILURE;

	} else if (!outFile){

		std::cerr << "Invalid output file: " << argv[2] << std::endl;
		return EXIT_FAILURE;

	}

	//read the file and store the information.
	std::vector<Vector4*> points;
	std::vector<Face*> faces;
	readFile(inFile, points, faces);

	inFile.close();
	outFile.close();

	return 0;

}

void readFile(std::ifstream &inFile, std::vector<Vector4*> &points, std::vector<Face*> &faces){

	std::string line;

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

			points.push_back(new Vector4(x, y, z, 1.0));

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
