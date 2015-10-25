
#include <algorithm>
#include <cassert>
#include <cmath>
#include <utility>

#include "Window.h"
#include "Face.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Light.h"

//Face will retain a pointer to these, but will not delete them
Face::Face(Vector4 *first, Vector4 *second, Vector4 *third){

	assert(first);
	assert(second);
	assert(third);

	pointOne = first;
	pointTwo = second;
	pointThree = third;

}

//renders the face
void Face::render(const Matrix4 &transform, const Matrix4 &windowingMatrix, const Vector4 &eyepoint, const Vector4 &material, 
				  const Light &ambient, const Light &point,  const float attenuation, const float shininess) const {

	Window *const win = Window::getWindow();

	//convert the coordinates to screen coordinates first
	Vector4 newFirst  = (transform * (*pointOne)).homogenize();
	Vector4 newSecond = (transform * (*pointTwo)).homogenize();
	Vector4 newThird  = (transform * (*pointThree)).homogenize();

	//calculate the normal of this face
	Vector4 v1 = newSecond - newFirst;
	Vector4 v2 = newThird - newFirst;
	Vector4 normal = (v2.cross(v1)).normalize();

	//this must be done in world space
	const Vector4 color1 = calculateColor(newFirst, normal, eyepoint, material, point, attenuation) + calculateColor(newFirst, normal, eyepoint, material, ambient, attenuation);
	const Vector4 color2 = calculateColor(newSecond, normal, eyepoint, material, point, attenuation) + calculateColor(newSecond, normal, eyepoint, material, ambient, attenuation);
	const Vector4 color3 = calculateColor(newThird, normal, eyepoint, material, point, attenuation) + calculateColor(newThird, normal, eyepoint, material, ambient, attenuation);

	//std::cout << "color1: " << color1;
	//std::cout << "color2: " << color2;
	//std::cout << "color3: " << color3;

	const Vector4 c1 = color2 - color1;
	const Vector4 c2 = color3 - color1;

	const Matrix4 mat = windowingMatrix * transform;

	//now move to screen space
	newFirst  = (mat * (*pointOne)).homogenize();
	newSecond = (mat * (*pointTwo)).homogenize();
	newThird  = (mat * (*pointThree)).homogenize();

	//calculate the normal of this face
	v1 = newSecond - newFirst;
	v2 = newThird - newFirst;
	normal = (v2.cross(v1)).normalize();

	//if the normal is facing away from the camera, do not render this face
	if (normal.z() < 0.0) return;

	//calculate the starting and ending x and y values for the polygon, but not outside the window
	const int xMin = round(fmax(fmin(fmin(newFirst.x(), newSecond.x()), newThird.x()), 0.0));
	const int yMin = round(fmax(fmin(fmin(newFirst.y(), newSecond.y()), newThird.y()), 0.0));

	const int xMax = round(fmin(fmax(fmax(newFirst.x(), newSecond.x()), newThird.x()), win->getWidth() - 1));
	const int yMax = round(fmin(fmax(fmax(newFirst.y(), newSecond.y()), newThird.y()), win->getHeight() - 1));

	//don't render if the polygon is off the screen either
	if (xMax < 0 || yMax < 0 || xMin >= win->getWidth() || yMin >= win->getHeight()) return;

	//calculate the alphas and betas and such for the start point of the bounding box
	const float denom   = 1.0 / ((v1.x() * v2.y()) - (v1.y() * v2.x()));
	const float dAlphaX = v2.y() * denom;
	const float dBetaX  = v1.y() * denom * -1.0;
	const float dAlphaY = v2.x() * denom * -1.0; 
	const float dBetaY  = v1.x() * denom;
	const float xPrime = xMin - newFirst.x();
	const float yPrime = yMin - newFirst.y();
	const float startAlpha = ((xPrime * v2.y()) - (yPrime * v2.x())) * denom;
	const float startBeta = ((yPrime * v1.x()) - (xPrime * v1.y())) * denom;

	//and the colors for each vertex
	//const Vector4 color1(1.0, 0.0, 0.0, 1.0);
	//const Vector4 color2(0.0, 1.0, 0.0, 1.0);
	//const Vector4 color3(0.0, 0.0, 1.0, 1.0);

	//diagnostic prints
	/*std::cout << "v1: " << v1;
	std::cout << "v2: " << v2;
	std::cout << "p1: " << newFirst;
	std::cout << "p2: " << newSecond;
	std::cout << "p3: " << newThird;
	std::cout << "n:  " << normal; 
	std::cout << "xmin:    " << xMin << std::endl;
	std::cout << "xmax:    " << xMax << std::endl;
	std::cout << "ymin:    " << yMin << std::endl; 
	std::cout << "yMax:    " << yMax << std::endl;
	std::cout << "denom:   " << denom << std::endl;
	std::cout << "alpha:   " << startAlpha << std::endl;
	std::cout << "beta:    " << startBeta << std::endl;
	std::cout << "dAlphaX: " << dAlphaX << std::endl;
	std::cout << "dAlphaY: " << dAlphaY << std::endl;
	std::cout << "dBetaX:  " << dBetaX << std::endl;
	std::cout << "dBetaY:  " << dBetaY << std::endl;
	std::cout << std::endl;*/

	//draw the pixels in the triangle
	for (int y = yMin; y <= yMax; ++y){

		//calculate alpha and beta for the incremental approach
		const int offset = y - yMin;
		float alpha = (startAlpha) + (offset * dAlphaY);
		float beta = (startBeta) + (offset * dBetaY);

		for (int x = xMin; x <= xMax; ++x){
			
			//use the slow way
			//const float pPrimeX = x - newFirst.x();
			//const float pPrimeY = y - newFirst.y();
			//const float alpha = ((pPrimeX * v2.y()) - (pPrimeY * v2.x())) * denom;
			//const float beta  = ((pPrimeY * v1.x()) - (pPrimeX * v1.y())) * denom;
			const float sum = alpha + beta;

			if ((alpha > 0.0) && (beta > 0.0) && (sum <= 1.0)){
				
				const float z = (v1.z() * alpha) + (v2.z() * beta) + newFirst.z();
				const float r = (c1.x() * alpha) + (c2.x() * beta) + color1.x();
				const float g = (c1.y() * alpha) + (c2.y() * beta) + color1.y();
				const float b = (c1.z() * alpha) + (c2.z() * beta) + color1.z();
				
				/*std::cout << "DRAWING" << std::endl;
				std::cout << "x:   " << x << std::endl;
				std::cout << "y:   " << y << std::endl;
				std::cout << "z:   " << z << std::endl;
				std::cout << "r:   " << r << std::endl;
				std::cout << "g:   " << g << std::endl;
				std::cout << "b:   " << b << std::endl;*/

				//draw using interpolated color
				win->drawPixel(x, y, 0.0, r, g, b);

				//draw using material color
				//win->drawPixel(x, y, 0.0, material.x(), material.y(), material.z());

			}

			//increment alpha and beta in the x direction
			alpha += dAlphaX;
			beta += dBetaX;

		}

	}

	//line drawing algorithms
	//renderDDA(newFirst, newSecond);
	//renderDDA(newSecond, newThird);
	//renderDDA(newThird, newFirst);
	//renderBresham(newFirst, newSecond);
	//renderBresham(newSecond, newThird);
	//renderBresham(newThird, newFirst);

}

//private methods ---------------------------------------------------------------------------------

Vector4 Face::calculateColor(const Vector4 &vertex, const Vector4 &normal, const Vector4 &eyepoint, 
							 const Vector4 &material, const Light &light, const float attenuation) const {

	//fudge factors
	const static float a = 1;
	const static float b = 1;
	const static float c = 1;

	//first, calculate l
	Vector4 l = light.getLocation() - vertex;
	const float distance = l.length();
	l = l.normalize();

	const float ldotN = l.dot(normal);

	//then r
	const Vector4 r = (normal * (ldotN * 2)) - l;

	//then v
	const Vector4 v = (eyepoint - vertex).normalize();

	const Vector4 diffuse  = (material * light.getColor()) * ldotN;
	const Vector4 specular =  Vector4::identity_p() * pow(r.dot(v), attenuation);
	const float denom = a + (b * distance) + (c * distance * distance);

	//std::cout << "diffuse: " << diffuse;
	//std::cout << "specular " << specular;
	//std::cout << "denom:   " << denom << std::endl;

	return ((diffuse + specular) / denom);

}

//implements the DDA line drawing algorithm
void Face::renderDDA(const Vector4 &start, const Vector4 &end) const {

	Vector4 one = start;
	Vector4 two = end;

	//for drawing pixels
	Window *const win = Window::getWindow();

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
			win->drawPixel(thisX, currentY, 0.0, 1, 0, 0);
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
			win->drawPixel(currentX, thisY, 0.0, 1, 0, 0);
			currentY += m;
			currentX++;

		}

	}

}

//implements the Bresham line drawing algorithm
void Face::renderBresham(const Vector4 &start, const Vector4 &end) const {

	Window *const win = Window::getWindow();

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
	win->drawPixel(xc, yc, 0.0, 0.0, 0.0, 1.0);

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

			win->drawPixel(xc, yc, 0.0, 0.0, 0.0, 1.0);

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

			win->drawPixel(xc, yc, 0.0, 0.0, 0.0, 1.0);

		}

	}

}
