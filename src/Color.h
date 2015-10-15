
#ifndef COLOR_H
#define COLOR_H

#include "Vector4.h"

class Color {

private:

	Vector4 data;

public:

	Color(const float r, const float g, const float b, const float a = 1.0) : data(r, g, b, a){}

	inline float r(){ return data.x();}
	inline float g(){ return data.y();}
	inline float b(){ return data.z();}
	inline float a(){ return data.w();}

};

#endif
