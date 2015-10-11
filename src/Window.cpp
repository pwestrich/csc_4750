
//for math constants, like pi
#define _USE_MATH_DEFINES

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include <GL/glut.h>

#include "Window.h"
#include "Scene.h"
#include "Matrix4.h"
#include "Vector4.h"
#include "AffineTransformations.h"

void display();
void resize(const int w, const int h);

Window *Window::getWindow(){

	static Window win;
	return &win;

}

void Window::initWindow(const int argc, const char **argv, const int width, const int height, const int x, const int y, 
					const char *title, const std::string &normalFile, const std::string &cameraFile){

	if (init) return;

	//init window settings
	glutInit(const_cast<int*>(&argc), const_cast<char**>(argv));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(x, y);
	glutCreateWindow(title);

	//background color black
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//set callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(resize);

	scene = new Scene();

	normalMatrix = createNormalMatrix(normalFile);
	cameraMatrix = createCameraMatrix(cameraFile);

	init = true;

}

Window::~Window(){

	if (scene){

		delete scene;
		scene = NULL;

	}

}

void Window::show(){

	glutMainLoop();

}

void Window::render() const {

	const Matrix4 windowing = getWindowingMatrix();
	const Matrix4 aspect = getAspectRatioMatrix();
	const Matrix4 final = windowing * normalMatrix * aspect * cameraMatrix;

	std::cout << "Windowing: " << windowing;
	std::cout << "Normal: " << normalMatrix;
	std::cout << "Aspect: " << aspect;
	std::cout << "Camera: " << cameraMatrix;
	std::cout << "Concatenated: " << final;

	scene->render(final);

}

//draws one pixel on the screen. Takes window coordinates.
void Window::drawPixel(const int x, const int y, const float r, const float g, const float b) const {

	const int w = glutGet(GLUT_WINDOW_WIDTH);
	const int h = glutGet(GLUT_WINDOW_HEIGHT);

	//convert the window coordinates to what openGL wants
	float xCanon = (x * 2.0) / w + (-1.0 * (w - 1)) / w;
	float yCanon = (-2.0 * y) / h + (1.0 * (h - 1)) / h;

	//set the pixel color
	glColor3f(r, g, b);

	//draw the pixel
	glBegin(GL_POINTS);
	glVertex2f(xCanon, yCanon);
	glEnd();

}

//get the width and height of the window 
int Window::getWidth() const {

	return glutGet(GLUT_WINDOW_WIDTH);

}

int Window::getHeight() const {

	return glutGet(GLUT_WINDOW_HEIGHT);

}

//private methods & functions ---------------------------------------------------------------------

Window::Window(){

	init = false;

}

//returns the matrix to convert window coordinates to screen coordinates
Matrix4 Window::getWindowingMatrix() const {

	float values[16] = {static_cast<float>((getHeight()) / 2.0), 0, 0, static_cast<float>((getWidth() - 1.0) / 2.0),
						0, static_cast<float>(getWidth() / -2.0), 0, static_cast<float>((getHeight() - 1.0) / 2.0), 
						0, 0, 1, 0,
						0, 0, 0, 1};

	return Matrix4(values);

}

//returns the normal matrix
Matrix4 Window::createNormalMatrix(const std::string &filename) {

	std::fstream inFile(filename);

	if (!inFile){

		std::cerr << "Invalid filename: " << filename << std::endl;
		exit(EXIT_FAILURE);

	}

	std::string buffer;
	std::vector<std::string> lines;

	do {

		getline(inFile, buffer);
		lines.push_back(buffer);

	} while (!inFile.eof());

	if (lines.size() != 7){

		std::cerr << "Error: File invalid: " << filename << std::endl;
		exit(EXIT_FAILURE);

	}

	//line 1 is the FOV
	fov = stof(lines[1]);

	//line 3 is zmax (near clip)
	float near = stof(lines[3]);

	//line 5 is zmin (far clip)
	float far = stof(lines[5]);

	inFile.close();

	//calculate the normal matrix
	float alpha = (near + far) / (far - near);
	float beta  = (2 * near * far) / (near - far);

	std::cout << "FOV:   " << fov   << std::endl;
	std::cout << "Near:  " << near  << std::endl;
	std::cout << "Far:   " << far   << std::endl;
	std::cout << "Alpha: " << alpha << std::endl;
	std::cout << "Beta:  " << beta  << std::endl;

	float values[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, alpha, beta, 0, 0, -1, 0};

	return Matrix4(values);

}

//returns the aspect matrix
Matrix4 Window::getAspectRatioMatrix() const {

	const float xMax = tan((M_PI * fov) / 360.0);
	const float yMax= (xMax * getHeight()) / getWidth();

	std::cout << "xmax: " << xMax << std::endl;
	std::cout << "ymax: " << yMax << std::endl;

	return createScaleMatrix(1.0 / xMax, 1.0 / yMax, 1.0);

}

//returns the camera matrix
Matrix4 Window::createCameraMatrix(const std::string &filename) const {

	std::fstream inFile(filename);

	if (!inFile){

		std::cerr << "Invalid filename: " << filename << std::endl;
		exit(EXIT_FAILURE);

	}

	std::string buffer;
	std::vector<std::string> lines;

	do {

		getline(inFile, buffer);
		lines.push_back(buffer);

	} while (!inFile.eof());

	if (lines.size() != 13){

		std::cerr << "Error: File invalid: " << filename << std::endl;
		exit(EXIT_FAILURE);

	}

	//lines 1, 2, 3 are the eye point
	const float ex = stof(lines[1]);
	const float ey = stof(lines[2]);
	const float ez = stof(lines[3]);

	const Vector4 E(ex, ey, ez, 1.0);

	//lines 5, 6, 7 are the at point
	const float ax = stof(lines[5]);
	const float ay = stof(lines[6]);
	const float az = stof(lines[7]);

	const Vector4 A(ax, ay, az, 1.0);

	//lines 9, 10, 11 are the up vector
	const float ux = stof(lines[9]);
	const float uy = stof(lines[10]);
	const float uz = stof(lines[11]);

	inFile.close();

	const Vector4 temp(ux, uy, uz, 0.0);
	const Vector4 vup = temp.normalize();

	//now calculate N, U, and V
	const Vector4 N = (E - A).normalize();

	//v is hard
	const float vdotN = vup.dot(N);
	const float vdotN2 = vdotN * vdotN;
	const float bottom = sqrt(1.0 - vdotN2);
	const float alpha = vdotN / bottom;
	const float beta = 1.0 / bottom;

	const Vector4 one = N * alpha;
	const Vector4 two = vup * beta;
	const Vector4 V = (one + two).normalize();

	//u isn't so bad now
	const Vector4 U = (V.cross(N)).normalize();

	//now we can work on the matrix
	const float edotU = -1.0 * E.dot(U);
	const float edotV = -1.0 * E.dot(V);
	const float eDotN = -1.0 * E.dot(N);

	std::cout << "Eyepoint: " << E;
	std::cout << "Atpoint:  " << A;
	std::cout << "V_up:     " << vup;
	std::cout << "N:        " << N;
	std::cout << "U:        " << U;
	std::cout << "V:        " << V;

	float values[16] = {U.x(), U.y(), U.z(), edotU,
						V.x(), V.y(), V.z(), edotV,
						N.x(), N.y(), N.z(), eDotN,
						0.0  , 0.0  , 0.0  , 1.0   };

	return Matrix4(values);

}

void display(){

	const int width = glutGet(GLUT_WINDOW_WIDTH);
	const int height = glutGet(GLUT_WINDOW_HEIGHT);

	resize(width, height);

}

void resize(const int w, const int h){

	glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_CULL_FACE);

	//draw the scene here
	static Window *win = Window::getWindow();
	win->render();

	glutSwapBuffers();
	glFlush();

}
