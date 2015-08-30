
#include <GL/glut.h>

#include "Window.h"
#include "Picture.h"

class Pixel;

void display();
void resize(const int w, const int h);

Window *Window::getWindow(){

	static Window win;
	return &win;

}

Window::~Window(){}

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

	init = true;

}

void Window::show(){

	glutMainLoop();

}

//draws one pixel on the screen, converting it to window coordinates
void Window::drawPixel(const int x, const int y, const float r, const float g, const float b){

	const int w = glutGet(GLUT_WINDOW_WIDTH);
	const int h = glutGet(GLUT_WINDOW_HEIGHT);

	//calculate the window coordinates
	float xCanon = (x * 2.0) / w + (-1.0 * (w - 1)) / w;
	float yCanon = (-2.0 * y) / h + (1.0 * (h - 1)) / h;

	//set the pixel color
	glColor3f(r, g, b);

	//draw the pixel
	glBegin(GL_POINTS);
	glVertex2f(xCanon, yCanon);
	glEnd();

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

	//draw the pixel here
	Picture *pic = Picture::getPicture();
	pic->render();

	glutSwapBuffers();
	glFlush();

}
