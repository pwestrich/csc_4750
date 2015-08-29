
#include <cassert>

#include "Face.h"
#include "Vertex.h"

//Face will retain a pointer to these, but will not delete them
Face::Face(Vertex *first, Vertex *second, Vertex *third){

	assert(first);
	assert(second);
	assert(third);

	pointOne = first;
	pointTwo = second;
	pointThree = third;

}

Face::~Face(){}
