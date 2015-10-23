
#ifndef FACE_H
#define FACE_H

class Matrix4;
class Vector4;

class Face {

private:

	Vector4 *pointOne;
	Vector4 *pointTwo;
	Vector4 *pointThree;

	//implements the DDA line drawing algorithm
	void renderDDA(const Vector4 &start, const Vector4 &end) const;

	//implements the Bresham line drawing algorithm
	void renderBresham(const Vector4 &start, const Vector4 &end) const;

public:

	//Face will retain a pointer to these, but will not delete them
	Face(Vector4 *first, Vector4 *second, Vector4 *third);
	~Face();

	inline Vector4 *getFirst() const { return pointOne;}
	inline Vector4 *getSecond() const { return pointTwo;}
	inline Vector4 *getThird() const { return pointThree;}

	//renders the face (draws only lines for now)
	void render(const Matrix4 &transform, const Matrix4 &windowingMatrix, const Vector4 &eyepoint, const Vector4 &material, const float attenuation) const;

};

#endif
