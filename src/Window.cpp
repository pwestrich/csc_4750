
//for math constants, like pi
#define _USE_MATH_DEFINES

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <GL/glut.h>

#include "Window.h"
#include "Scene.h"

const float Z_MIN = 1.0;
const float Z_MAX = 1.0;
const float FOV_X = 90.0;

const std::string FILE_SHADER_VERTEX   = "data/vertex_shader_Texture.txt";
const std::string FILE_SHADER_FRAGMENT = "data/fragment_shader_Texture.txt";
const std::string FILE_SHADER_GEOMETRY = "data/geometry_shader_Texture.txt";

char *readText(const std::string &filename);
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

	std::cout << "Using GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;
	/*
	int status = 0;

	//create shaders
	GLuint vertexShader   = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

	//read in shader text
	char *const vertexData   = readText(FILE_SHADER_VERTEX);
	char *const fragmentData = readText(FILE_SHADER_FRAGMENT);
	char *const geometryData = readText(FILE_SHADER_GEOMETRY);

	//compile shaders
	glShaderSource(vertexShader, 1, &vertexData, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE){

		std::cerr << "Vertex shader compilation failed: " << status << std::endl;
		exit(EXIT_FAILURE);

	}

	glShaderSource(fragmentShader, 1, &fragmentData, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE){

		std::cerr << "Fragment shader compilation failed: " << status << std::endl;
		exit(EXIT_FAILURE);

	}

	glShaderSource(geometryShader, 1, &geometryData, NULL);
	glCompileShader(geometryShader);
	glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE){

		std::cerr << "Geometry shader compilation failed: " << status << std::endl;
		exit(EXIT_FAILURE);

	}

	GLuint program = glCreateProgram();

	//set what inputs and outputs each shader gets
	glProgramParameteriEXT(program, GL_GEOMETRY_INPUT_TYPE_EXT, GL_TRIANGLES);
	glProgramParameteriEXT(program, GL_GEOMETRY_OUTPUT_TYPE_EXT, GL_TRIANGLE_STRIP);
	glProgramParameteriEXT(program, GL_GEOMETRY_VERTICES_OUT_EXT, 3);

	glAttachShader(program, vertexShader);
	glAttachShader(program, geometryShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (!status){

		std::cerr << "Error: Shaders could not be linked: " << status << std::endl;
		exit(EXIT_FAILURE);

	}

	glUseProgram(program);

	//place a value into a GPU register
	GLint loc = glGetUniformLocation(program, "image_1");
	//use texture unit 3 for one of the images
	glUniform1i(loc, 3);

	loc = glGetUniformLocation(program, "image_2");
	//use texture unit 1 for one of the images
	glUniform1i(loc, 1);*/

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

char *readText(const std::string &filename){

	std::ifstream inFile(filename);

	if (!inFile){

		std::cerr << "Error opening file: " << filename << std::endl;
		exit(EXIT_FAILURE);

	}

	//determine length of file
	inFile.seekg(0, std::ios::end);
	const int length = inFile.tellg();

	char *data = new char[length];

	//read file
	inFile.seekg(0, std::ios::beg);
	inFile.read(data, length);

	return data;

}

void display(){

	const int width = glutGet(GLUT_WINDOW_WIDTH);
	const int height = glutGet(GLUT_WINDOW_HEIGHT);

	resize(width, height);

}

void resize(const int w, const int h){

	//resize the viewport
	glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));	

	//clear the buffers
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	//set the perspective matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	const float ratio = static_cast<float>(h) / w;
	const float fov_y = 2.0 * atan(tan(FOV_X * 0.5) / ratio);
	gluPerspective(fov_y, ratio, Z_MAX, Z_MIN);

	//render the scene
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	static Window *win = Window::getWindow();
	win->render();

	//swap and flush buffers
	glutSwapBuffers();
	glFlush();

}
