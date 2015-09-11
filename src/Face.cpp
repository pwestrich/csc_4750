
#include <cassert>
#include <cmath>
#include <utility>

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
void Face::render(const Matrix4 &transform) const {

	//convert the coordinates to screen coordinates first
	const Vector4 newFirst  = (transform * pointOne->vector());
	const Vector4 newSecond = (transform * pointTwo->vector());
	const Vector4 newThird  = (transform * pointThree->vector());

	//draw using the DDA algorithm first
	renderDDA(newFirst, newSecond);
	renderDDA(newSecond, newThird);
	renderDDA(newThird, newFirst);

	//then draw the Bresham version on top of it
	renderBresham(newFirst, newSecond);
	renderBresham(newSecond, newThird);
	renderBresham(newThird, newFirst);

}

//private methods ---------------------------------------------------------------------------------

//implements the DDA line drawing algorithm
void Face::renderDDA(const Vector4 &start, const Vector4 &end) const {

	Vector4 one = start;
	Vector4 two = end;

	//for drawing pixels
	const Window *win = Window::getWindow();

	//compute the parameters of our line
	float m = (two.y() - one.y()) / (two.x() - one.x());

	if ((m < -1.0) || (m > 1.0)){

		if (two.y() <= one.y()){

			std::swap(one, two);

		}

		//use 1 / m and loop over y
		m = 1.0 / m;
		float b = two.y() - (m * two.x());
		int currentY = round(one.y());
		int endY = round(two.y());

		float currentX = round(one.x());

		while (currentY <= endY){

			int thisX = round(currentX);
			win->drawPixel(thisX, currentY, 1, 0, 0);
			currentX += m;
			currentY++;

		}

	} else {

		//use m and loop over x
		float b = two.y() - (m * two.x());

		if (two.x() <= one.x()){

			std::swap(one, two);

		}

		int currentX = round(one.x());
		int endX = round(two.x());

		float currentY = (m * currentX) + b;

		while (currentX <= endX){

			int thisY = round(currentY);
			win->drawPixel(currentX, thisY, 1, 0, 0);
			currentY += m;
			currentX++;

		}

	}

}

//implements the Bresham line drawing algorithm
void Face::renderBresham(const Vector4 &start, const Vector4 &end) const {

	const Window *win = Window::getWindow();

	//calculate the change in x and y
	int dx = round(end.x() - start.x());
	int dy = round(end.y() - start.y());

	//calculate the increment in x and y
	int xInc = ((dx > 0) - (dx < 0));
	int yInc = ((dy > 0) - (dy < 0));

	//convert changes into positive double themselves
	dx = abs(dx) << 1;
	dy = abs(dy) << 1;

	//get our starting and ending x and y
	int xc = round(start.x());
	int yc = round(start.y());
	int xf = round(end.x());
	int yf = round(end.y());

	//draw the starting point and begin the loop
	win->drawPixel(xc, yc, 0.0, 0.0, 1.0);

	if (dx > dy){

		int e = dy - (dx >> 1);

		while (xc < xf){

			if ((e >= 0) && (e || xInc > 0)){

				e -= dx;
				yc += yInc;

			}

			e += dy;
			xc += xInc;

			win->drawPixel(xc, yc, 0.0, 0.0, 1.0);

		}

	} else {

		int e = dx - (dy >> 1);

		while (yc < yf){

			if ((e >= 0) && (e || (yInc > 0))){

				e -= dy;
				xc += xInc;

			}

			e += dx;
			yc += yInc;

			win->drawPixel(xc, yc, 0.0, 0.0, 1.0);

		}

	}

}
