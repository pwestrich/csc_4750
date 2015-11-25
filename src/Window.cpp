
//for math constants, like pi
#define _USE_MATH_DEFINES

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GL/glut.h>

#include "Window.h"
#include "Scene.h"

void display();
void resize(const int w, const int h);

Window *Window::getWindow(){

	static Window win;
	return &win;

}

void Window::initWindow(const int argc, const char **argv, const int width, const int height, const int x, const int y, const char *title){

	if (init) return;

	//init window settings
	glutInit(const_cast<int*>(&argc), const_cast<char**>(argv));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(x, y);
	glutCreateWindow(title);

	//background color black
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//set a few opther things
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	//what in the world do these do?
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	//set callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(resize);

	//init shaders
	GLenum err = glewInit();
	if (err){

		std::cerr << "Error initializing GLUT: " << err << std::endl;
		exit(EXIT_FAILURE);

	}

	/*glProgramParameteriEXT(program, GL_GEOMETRY_INPUT_TYPE_EXT, GL_TRIANGLES);
	glProgramParameteriEXT(program, GL_GEOMETRY_OUTPUT_TYPE_EXT, GL_TRIANGLE_STRIP);
	glProgramParameteriEXT(program, GL_GEOMETRY_VERTICES_OUT_EXT, 3);*/

	//initialize scene
	scene = new Scene();

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

void Window::render(){

	//travesrse the scene graph
	scene->render();

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
	glClear(GL_DEPTH_BUFFER_BIT);

	//draw the scene here
	static Window *win = Window::getWindow();
	win->render();

	glutSwapBuffers();
	glFlush();

}
