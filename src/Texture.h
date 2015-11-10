
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Vector4;

class Texture {

private:

	//the data read in from the file
	unsigned char *data;

	//dimensions of the texture
	int width;
	int height;

public:

	Texture(const std::string &filename, const int w, const int h);
	Texture(const Texture&) 			= delete;
	Texture& operator=(const Texture&)  = delete;
	~Texture();

	//getter methods -- getData returns a pointer to the data, but retains ownership of it
	inline const unsigned char* getData() const { return data;}
	inline int getWidth() const { return width;}
	inline int getHeight() const { return height;}

	Vector4 getColor(const float t, const float s) const;

};

#endif
