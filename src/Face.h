
#ifndef FACE_H
#define FACE_H

class Matrix4;
class Vertex;
class Vector4;

class Face {

private:

	Vertex *pointOne;
	Vertex *pointTwo;
	Vertex *pointThree;

	//Vector3 normal //future

	//implements the DDA line drawing algorithm
	void renderDDA(const Vector4 &start, const Vector4 &end) const;

	//implements the Bresham line drawing algorithm
	void renderBresham(const Vector4 &start, const Vector4 &end) const;

public:

	//Face will retain a pointer to these, but will not delete them
	Face(Vertex *first, Vertex *second, Vertex *third);
	~Face();

	inline Vertex *getFirst() const { return pointOne;}
	inline Vertex *getSecond() const { return pointTwo;}
	inline Vertex *getThird() const { return pointThree;}

	//renders the face (draws only lines for now)
	void render(const Matrix4 &transform) const;

};

#endif
