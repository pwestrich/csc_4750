
#include <algorithm>
#include <cassert>
#include <cmath>
#include <utility>

#include "Window.h"
#include "Face.h"
#include "Vector4.h"
#include "Matrix4.h"

//Face will retain a pointer to these, but will not delete them
Face::Face(Vector4 *first, Vector4 *second, Vector4 *third){

	assert(first);
	assert(second);
	assert(third);

	pointOne = first;
	pointTwo = second;
	pointThree = third;

}

Face::~Face(){}

//renders the face
void Face::render(const Matrix4 &transform) const {

	const Window *win = Window::getWindow();

	//convert the coordinates to screen coordinates first
	const Vector4 newFirst  = (transform * (*pointOne)).homogenize();
	const Vector4 newSecond = (transform * (*pointTwo)).homogenize();
	const Vector4 newThird  = (transform * (*pointThree)).homogenize();

	//calculate the normal of this face
	const Vector4 v1 = newSecond - newFirst;
	const Vector4 v2 = newThird - newFirst;
	const Vector4 normal = v1.cross(v2).normalize();

	//if the normal is facing away from the camera, do not render this face
	if (normal.z() < 0.0) return;

	//calculate the starting and ending x and y values for the polygon, but not outside the window
	const int xMin = round(fmax(fmin(fmin(newFirst.x(), newSecond.x()), newThird.x()), 0.0));
	const int yMin = round(fmax(fmin(fmin(newFirst.y(), newSecond.y()), newThird.y()), 0.0));

	const int xMax = round(fmin(fmax(fmax(newFirst.x(), newSecond.x()), newThird.x()), win->getWidth()));
	const int yMax = round(fmin(fmax(fmax(newFirst.y(), newSecond.y()), newThird.y()), win->getHeight()));

	//next calculate the change in x and y for the lines
	const float denom = (v1.x() * v2.y()) - (v1.y() * v2.x());
	float alpha = ((xMin * v2.y()) - (yMin * v2.x())) / denom;
	const float beta = ((yMin * v1.y()) - (xMin * v1.y())) / denom;

	const float dAlpha = v2.y() / denom;
	const float dBeta = v1.x() / denom;

	//draw the polygon
	for (int i = xMin; i <= xMax; ++i){

		float thisBeta = beta;

		if (alpha > 0.0){

			for (int j = yMin; j <= yMax; ++j){

				const float sum = alpha + thisBeta;

				//draw point
				if (thisBeta > 0.0 && sum <= 1.0){

					win->drawPixel(i, j, 0, 1, 0);

				}

				thisBeta += dBeta;

			}

		}

		alpha += dAlpha;

	}

	//draw using the DDA algorithm first
	//renderDDA(newFirst, newSecond);
	//renderDDA(newSecond, newThird);
	//renderDDA(newThird, newFirst);

	//then draw the Bresham version on top of it
	//renderBresham(newFirst, newSecond);
	//renderBresham(newSecond, newThird);
	//renderBresham(newThird, newFirst);

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
	int dx = round(end.x()) - round(start.x());
	int dy = round(end.y()) - round(start.y());

	//calculate the increment in x and y
	const int xInc = ((dx > 0) - (dx < 0));
	const int yInc = ((dy > 0) - (dy < 0));

	//convert changes into positive double themselves
	dx = abs(dx) << 1;
	dy = abs(dy) << 1;

	//get our starting and ending x and y
	int xc = round(start.x());
	int yc = round(start.y());
	const int xf = round(end.x());
	const int yf = round(end.y());

	//draw the starting point and begin the loop
	win->drawPixel(xc, yc, 0.0, 0.0, 1.0);

	if (dx > dy){

		int e = dy - (dx >> 1);

		//loop over x case
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

		//loop over y case
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
