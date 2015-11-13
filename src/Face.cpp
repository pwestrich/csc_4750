
#include <algorithm>
#include <cassert>
#include <cmath>
#include <utility>

#include "Window.h"
#include "Face.h"
#include "Vector4.h"
#include "Vertex.h"
#include "Matrix4.h"
#include "Light.h"
#include "Texture.h"

//Face will retain a pointer to these, but will not delete them
Face::Face(Vertex *const first, Vertex *const second, Vertex *const third) 
		: pointOne(first), pointTwo(second), pointThree(third) {

	assert(first);
	assert(second);
	assert(third);

}

Vector4 Face::getNormal(const Matrix4 &transform) const {

	//convert the coordinates to screen coordinates first
	Vector4 newFirst  = transform * pointOne->vector();
	Vector4 newSecond = transform * pointTwo->vector();
	Vector4 newThird  = transform * pointThree->vector();

	//calculate the normal of this face
	Vector4 v1 = newSecond - newFirst;
	Vector4 v2 = newThird - newFirst;
	return  (v2.cross(v1)).normalize();

}

void Face::addTextureCoordinates(const TextureCoordinates &coords){

	texCoords.push_back(coords);

}

//renders the face
void Face::render(const Matrix4 &transform, const Matrix4 &windowingMatrix, const Vector4 &eyepoint, const Vector4 &material, 
				  const Light &ambient, const Light &point, const Texture &tex,  const float attenuation, const float shininess) const {

	Window *const win = Window::getWindow();

	//this must be done in world space
	const Vector4 color1 = calculateColor(*pointOne, transform, eyepoint, material, point, ambient, attenuation, shininess);
	const Vector4 color2 = calculateColor(*pointTwo, transform, eyepoint, material, point, ambient, attenuation, shininess); 
	const Vector4 color3 = calculateColor(*pointThree, transform, eyepoint, material, point, ambient, attenuation, shininess);

	const Vector4 c1 = color2 - color1;
	const Vector4 c2 = color3 - color1;

	const Matrix4 mat = windowingMatrix * transform;

	//now move to screen space
	const Vector4 newFirst  = (mat * pointOne->vector()).homogenize();
	const Vector4 newSecond = (mat * pointTwo->vector()).homogenize();
	const Vector4 newThird  = (mat * pointThree->vector()).homogenize();

	//calculate the normal of this face
	const Vector4 v1 = newSecond - newFirst;
	const Vector4 v2 = newThird - newFirst;
	const Vector4 normal = (v2.cross(v1)).normalize();

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

	//draw the pixels in the triangle
	for (int y = yMin; y <= yMax; ++y){

		//calculate alpha and beta for the incremental approach
		const int offset = y - yMin;
		float alpha = (startAlpha) + (offset * dAlphaY);
		float beta = (startBeta) + (offset * dBetaY);

		for (int x = xMin; x <= xMax; ++x){

			const float sum = alpha + beta;

			if ((alpha > 0.0) && (beta > 0.0) && (sum <= 1.0)){
				
				const float z = (v1.z() * alpha) + (v2.z() * beta) + newFirst.z();
				const float r = (c1.x() * alpha) + (c2.x() * beta) + color1.x();
				const float g = (c1.y() * alpha) + (c2.y() * beta) + color1.y();
				const float b = (c1.z() * alpha) + (c2.z() * beta) + color1.z();

				//draw using interpolated color
				win->drawPixel(x, y, 0.0, r, g, b);

			}

			//increment alpha and beta in the x direction
			alpha += dAlphaX;
			beta += dBetaX;

		}

	}

}

//private methods ---------------------------------------------------------------------------------

Vector4 Face::calculateColor(const Vertex &vertex, const Matrix4 &transform, const Vector4 &eyepoint, const Vector4 &material,
							 const Light &light, const Light &ambient, const float attenuation, const float shininess) const {

	//get the average normal for this point
	const Vector4 normal = vertex.averageNormal(transform);
	const Vector4 point = transform * vertex.vector();

	//first, calculate l
	Vector4 l = point - light.getLocation();
	const float distance = l.length();
	l = l.normalize();

	float ldotN = l.dot(normal);

	if (ldotN < 0.0) ldotN = 0.0;

	//then r
	const Vector4 r = (normal * (ldotN * 2)) - l;

	//then v
	const Vector4 v = (point - eyepoint).normalize();

	float rdotV = r.dot(v);

	if (rdotV < 0.0) rdotV = 0.0;


	const Vector4 diffuse  = (material * light.getColor()) * ldotN;
	const Vector4 specular =  Vector4::identity_p() * pow(rdotV, shininess);
	const float denom = (attenuation * distance);

	const Vector4 color = (diffuse + specular + ambient.getColor()) / denom;

	/*std::cout << "color:   " << color;
	std::cout << "diffuse: " << diffuse;
	std::cout << "specular " << specular;
	std::cout << "atten:   " << attenuation << std::endl;
	std::cout << "shiny:   " << shininess << std::endl;
	std::cout << "l.n:     " << ldotN << std::endl;
	std::cout << "r.v:     " << rdotV << std::endl; 
	std::cout << "denom:   " << denom << std::endl << std::endl;*/

	return color;

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
