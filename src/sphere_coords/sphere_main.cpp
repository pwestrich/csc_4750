
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//borrow some things from the program
#include "../Vector4.h"
#include "../utilities.h"

//a face of the object
struct Face {

	Vector4 *const one;
	Vector4 *const two;
	Vector4 *const three;

	Face(Vector4 *_one, Vector4 *_two, Vector4 *_three) : one(_one), two(_two), three(_three){}

};

//the texture coordinates of a face
struct TextureCoordinate {

	float s1;
	float s2;
	float s3;
	float t1;
	float t2;
	float t3;

};

void readFile(std::ifstream &inFile, std::vector<Vector4*> &points, std::vector<Face*> &faces);
void writeFile(std::ifstream &inFile, std::ofstream &outFile, const std::vector<TextureCoordinate> &coords);
void printFaces(const std::vector<Face*> faces);

inline float adjustS(const Vector4 &point, const float s){

	if (point.x() > 0.0 && point.z() > 0.0){

		return s;

	} else if (point.z() > 0.0 && point.x() < 0.0){

		return s + 1.0;

	} else return s + 0.5;

}

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

	std::vector<TextureCoordinate> coords(faces.size());

	for (size_t i = 0; i < faces.size(); ++i){

		//calculate the texture coordinates for each vertex
		const float p_1 = sqrt(faces[i]->one->dot(*faces[i]->one)); 
		const float p_2 = sqrt(faces[i]->two->dot(*faces[i]->two)); 
		const float p_3 = sqrt(faces[i]->three->dot(*faces[i]->three));

		const float theta1 = acos(faces[i]->one->y() / p_1);
		const float theta2 = acos(faces[i]->two->y() / p_2);
		const float theta3 = acos(faces[i]->three->y() / p_3);

		const float phi1 = atan(faces[i]->one->x() / faces[i]->one->z());
		const float phi2 = atan(faces[i]->two->x() / faces[i]->two->z());
		const float phi3 = atan(faces[i]->three->x() / faces[i]->three->z());

		//t is easy
		coords[i].t1 = 1.0 - (theta1 / M_PI);
		coords[i].t2 = 1.0 - (theta2 / M_PI);
		coords[i].t3 = 1.0 - (theta3 / M_PI);

		//s is not
		coords[i].s1 = adjustS(*faces[i]->one, (phi1 / (2.0 * M_PI)));
		coords[i].s2 = adjustS(*faces[i]->two, (phi2 / (2.0 * M_PI)));
		coords[i].s3 = adjustS(*faces[i]->three, (phi3 / (2.0 * M_PI)));

	}

	//write back to file
	inFile.clear();
	inFile.seekg(0, ios::beg);

	writeFile(inFile, outFile, coords);

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

void writeFile(std::ifstream &inFile, std::ofstream &outFile, const std::vector<TextureCoordinate> &coords){

	//first, write entire input file to the output file
	std::string line;

	getline(inFile, line, '\n');

	while (!inFile.eof()){

		if (line.find("end") == 0) break;

		outFile << line << std::endl;
		getline(inFile, line, '\n');

	}

	outFile << std::endl;

	//now write the texture coordinates to the file.
	for (size_t i = 0; i < coords.size(); ++i){

		outFile << "vt " << coords[i].s1 << " " << coords[i].t1 
				<< " "   << coords[i].s2 << " " << coords[i].t2
				<< " "   << coords[i].s3 << " " << coords[i].t3
				<< std::endl;

	}

	outFile << std::endl << "end of file" << std::endl;

}

void printFaces(const std::vector<Face*> faces){

	for (size_t i = 0; i < faces.size(); ++i){

		std::cout << "Face " << i << ": " << *faces[i]->one << *faces[i]->two << *faces[i]->three;

	}

}

