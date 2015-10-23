
#ifndef LIGHT_H
#define LIGHT_H

#include "Vector4.h"

class Light {

private:

	//location and color
	Vector4 location;
	Vector4 color;

public:

	Light(const float r, const float g, const float b, const float x, const float y, const float z) : location(x, y, z, 1.0), color(r, g, b, 1.0){}
	Light(const Vector4 &_color, const Vector4 &_location) : location(_location), color(_color){}
	Light() : Light(0.0, 0.0, 0.0, 0.0, 0.0, 0.0){}

	inline Vector4 getLocation() const { return location;}
	inline Vector4 getColor()    const { return color;   }

};

#endif
