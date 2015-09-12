
#include <GL/glut.h>

#include "Window.h"
#include "Scene.h"
#include "Matrix4.h"

class Pixel;

void display();
void resize(const int w, const int h);

Window *Window::getWindow(){

	static Window win;
	return &win;

}

void Window::initWindow(const int argc, const char**argv, const int width, const int height, const int x, const int y, const char *title){

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

	scene = std::make_shared<Scene>();

	init = true;

}

void Window::show(){

	glutMainLoop();

}

void Window::render() const {

	const Matrix4 windowing = getWindowingMatrix();
	const Matrix4 aspect = getAspectRatioMatrix();

	scene->render(windowing * aspect);

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

//returns the matrix to convert window coordinates to screen coordinates
Matrix4 Window::getWindowingMatrix() const {

	float values[16] = {static_cast<float>(getHeight() / 2.0), 0, 0, static_cast<float>((getWidth() - 1.0) / 2.0), 0, static_cast<float>(getWidth() / -2.0), 0, static_cast<float>((getHeight() - 1.0) / 2.0), 0, 0, 1, 0, 0, 0, 0, 1};
	//float values[16] = {400.0, 0.0, 0.0, 399.5, 0.0, -300.0, 0.0, 299.5, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0};
	return Matrix4(values);

}

//returns the aspect matrix
Matrix4 Window::getAspectRatioMatrix() const {

	float values[16] = {1, 0, 0, 0, 0, static_cast<float>(getHeight() / static_cast<float>(getWidth())), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	//float values[16] = {1.0, 0.0, 0.0, 0.0, 0.0, (2.0 / 1.5), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0};
	return Matrix4(values);

}

//private methods & functions ---------------------------------------------------------------------

Window::Window(){

	init = false;

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
