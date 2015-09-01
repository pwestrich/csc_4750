
#include <cassert>
#include <cmath>

#include "Window.h"
#include "Face.h"
#include "Vertex.h"
#include "Vector4.h"
#include "Matrix4.h"

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

//renders the face (draws only lines for now)
void Face::render() const {

	const Window *win = Window::getWindow();

	const Matrix4 aspect = win->getAspectRatioMatrix();
	const Matrix4 windowing = win->getWindowingMatrix();

	//convert the coordinates to screen coordinates first
	const Vector4 newFirst  = windowing * aspect * pointOne->vector();
	const Vector4 newSecond = windowing * aspect * pointTwo->vector();
	const Vector4 newThird  = windowing * aspect * pointThree->vector();

	//draw using the DDA algorithm first
	renderDDA(newFirst, newSecond);
	renderDDA(newSecond, newThird);
	renderDDA(newThird, newFirst);

	//then draw the Bresham version on top of it
	//renderBresham(newFirst, newSecond);
	//renderBresham(newSecond, newThird);
	//renderBresham(newThird, newFirst);

}

//private methods ---------------------------------------------------------------------------------

//implements the DDA line drawing algorithm
void Face::renderDDA(const Vector4 &start, const Vector4 &end) const {

	const Window *win = Window::getWindow();

	//compute the parameters of our line
	float m = (end.y() - start.y()) / (end.x() - start.x());
	float b = end.y() - (m * end.x());

	if (m < 1.0){

		//use 1 / m and loop over y
		m = 1.0 / m;
		int currentY = round(start.y());
		int endY = round(end.y());

		float currentX = (m * currentY) + b;

		while (currentY <= endY){

			int thisX = round(currentX);
			win->drawPixel(thisX, currentY, 1, 0, 0);
			currentX += m;
			currentY++;

		}

	} else {

		//use m and loop over x

		int currentX = round(start.x());
		int endX = round(start.x());

		float currentY = (m * currentX) + b;

		while (currentX <= endX){

			int thisY = round(currentY);
			win->drawPixel(currentX, thisY, 0, 0, 1);
			currentY += m;
			currentX++;

		}

	}

}

//implements the Bresham line drawing algorithm
void Face::renderBresham(const Vector4 &start, const Vector4 &end) const {



}
