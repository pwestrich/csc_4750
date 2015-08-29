
#ifndef FACE_H
#define FACE_H

class Vertex;

class Face {

private:

	Vertex *pointOne;
	Vertex *pointTwo;
	Vertex *pointThree;

	//Vector3 normal //future

public:

	//Face will retain a pointer to these, but will not delete them
	Face(Vertex *first, Vertex *second, Vertex *third);
	~Face();

	inline Vertex *getFirst() const { return pointOne;}
	inline Vertex *getSecond() const { return pointTwo;}
	inline Vertex *getThird() const { return pointThree;}

};

#endif
