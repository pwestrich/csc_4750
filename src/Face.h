
#ifndef FACE_H
#define FACE_H

#include <vector>

#include "Vector4.h"
#include "Vertex.h"
#include "Texture.h"

class Matrix4;
class Light;

class Face {

private:

	Vertex *const pointOne;
	Vertex *const pointTwo;
	Vertex *const pointThree;

	std::vector<TextureCoordinates> texCoords;

	float calculateLighting(const Vertex &vertex, const Matrix4 &transform, const Light &light) const;

	//function to calcualte color
	/*Vector4 calculateColor(const Vertex &vertex, const Matrix4 &transform, const Vector4 &eyepoint, const Vector4 &material, 
						   const Light &light, const Light &ambient, const float attenuation, const float shininess) const;*/
	

	//implements the DDA line drawing algorithm
	void renderDDA(const Vector4 &start, const Vector4 &end) const;

	//implements the Bresham line drawing algorithm
	void renderBresham(const Vector4 &start, const Vector4 &end) const;

public:

	//Face will retain a pointer to these, but will not delete them
	Face(Vertex *const first, Vertex *const second, Vertex *const third);

	inline Vector4 getFirst() const { return pointOne->vector();}
	inline Vector4 getSecond() const { return pointTwo->vector();}
	inline Vector4 getThird() const { return pointThree->vector();}

	Vector4 getNormal(const Matrix4 &transform) const;

	void addTextureCoordinates(const float s, const float t);

	//renders the face (draws only lines for now)
	void render(const Matrix4 &transform, const Matrix4 &windowingMatrix, const Vector4 &eyepoint, const Vector4 &material, 
				const Light &ambient, const Light &point, const Texture &tex, const float attenuation, const float shininess) const;

};

#endif
