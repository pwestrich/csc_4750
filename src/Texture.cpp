
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

#include "Texture.h"
#include "Vector4.h"

Texture::Texture(const std::string &filename, const int w, const int h){

	data = NULL;
	height = h;
	width = w;

	//open the datafile as a binary stream
	std::ifstream inFile(filename, std::ios::binary | std::ios::in);

	if (!inFile){

		std::cerr << "Error opening file: " << filename << std::endl;
		exit(EXIT_FAILURE);

	}

	//start reading in stuff
	size = w * h * 3;						//expected size
	inFile.seekg(0, inFile.end);
	const int fileLength = inFile.tellg();	//actual size

	if (fileLength != size){

		std::cerr << "Error: Expected file length " << size << ", actual file length was " << fileLength << "." << std::endl;
		exit(EXIT_FAILURE);

	}

	data = new unsigned char[size];
	inFile.seekg(0, inFile.beg);
	inFile.read(reinterpret_cast<char*>(data), size);
	inFile.close();

}

Texture::~Texture(){

	if (data){

		delete [] data;
		data = NULL;

	}

}

Vector4 Texture::getColor(const float s, const float t) const {

	//calculate the texel coordinate
	const int tTexel = height - (static_cast<int>(height * t) % height) - 1; //t must be flipped
	const int sTexel = static_cast<int>(width * s) % width;
	const int index = ((tTexel * width) + sTexel) * 3;

	//the data is stored as unsigned ints. Divide by 255 to get a float from 0-1.
	const float r = data[index + 0] / 255.0;
	const float g = data[index + 1] / 255.0;
	const float b = data[index + 2] / 255.0;

	return Vector4(r, g, b, 1.0);

}
