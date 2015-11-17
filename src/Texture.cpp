
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

	//start readg in stuff
	const int size = w * h * 3;
	data = new unsigned char[size];

	inFile.read(reinterpret_cast<char*>(data), size);
	inFile.close();

}

Texture::~Texture(){

	if (data){

		delete [] data;
		data = NULL;

	}

}

Vector4 Texture::getColor(const float t, const float s) const {

	//calculate the texel coordinate
	const int tTexel = height - (static_cast<int>(height * t) % height) - 1;
	const int sTexel = static_cast<int>(width * s) % width;
	const int index = ((tTexel * width) + sTexel) * 3;

	const float r = data[index + 0] / 255.0;
	const float g = data[index + 1] / 255.0;
	const float b = data[index + 2] / 255.0;

	return Vector4(r, g, b, 1.0);

}
