#include <GL/glew.h>
#include <GL/glut.h>
#include "Window.h"
#include "Picture.h"
#include "ReadObject.h"
#include <iostream>
using namespace std;

void Window::staticDisplay()
{
   int width, height;
   width = glutGet(GLUT_WINDOW_WIDTH);
   height = glutGet(GLUT_WINDOW_HEIGHT);
   reshape(width, height);
}

void Window::display(int w, int h)  //callback for window drawing
{
   Picture picture;
   picture.render(w, h);

   glutSwapBuffers();  //for double buffering
   glFlush();  //forces completion of drawing
}

void Window::reshape(int w, int h)  //callback for window resizing
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   display(w, h);  //need this here to make the callback work correctly
}

void Window::show()
{
   glutMainLoop();  //show everything
}

Window::~Window(){}

Window::Window(int argc, char** argv, int width, int height, int xLoc, int yLoc, const char* title)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //use rgb color and double buffering 
   
   glutInitWindowSize(width, height);

   glutInitWindowPosition(xLoc, yLoc);  //place the window near the center of the screen
   glutCreateWindow(title);

   glClearColor(0.0, 0.0, 0.0, 1.0);  //background color is black

   glutDisplayFunc(Window::staticDisplay);  //set the repaint callback function (redraws after window has been resized)
   glutReshapeFunc(Window::reshape);        //set the reshape callback function (redraws while window is resized)

   //don't show back facing polygons
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);

   //enable z-buffering
   glEnable(GL_DEPTH_TEST);

   //enable lighting
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_NORMALIZE);  //makes sure that normals have unit length (slow)

   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);



   //GLEW

   //compile, link, and use shader programs
   GLenum err = glewInit();
   cout << "using glew version " << glewGetString(GLEW_VERSION) << endl;

   const char* fileName = "vertex_shader_Texture.txt";
   GLchar* str_v = getText(fileName);

   int status;  //compilation status

   GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertShader, 1, (const GLchar**)&str_v, NULL);
   glCompileShader(vertShader);
   glGetShaderiv(vertShader, GL_COMPILE_STATUS, &status);
   if (status == GL_FALSE)
   { 
      cout << "vertex shader compilation failed" << endl;
   }
   else
   {
      cout << "vertex shader compilation successful" << endl;
   }

   fileName = "fragment_shader_Texture.txt";
   GLchar* str_f = getText(fileName);

   GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragShader, 1, (const GLchar**)&str_f, NULL);
   glCompileShader(fragShader);
   glGetShaderiv(fragShader, GL_COMPILE_STATUS, &status);
   if (status == GL_FALSE)
   { 
      cout << "fragment shader compilation failed" << endl;
   }
   else
   {
      cout << "fragment shader compilation successful" << endl;
   }

   fileName = "geometry_shader_Texture.txt";    
   GLchar* str_g = getText(fileName);

   GLuint geomShader = glCreateShader(GL_GEOMETRY_SHADER_EXT);  
   glShaderSource(geomShader, 1, (const GLchar**)&str_g, NULL);
   glCompileShader(geomShader);
   glGetShaderiv(geomShader, GL_COMPILE_STATUS, &status);
   if (status == GL_FALSE)
   { 
      cout << "geometry shader compilation failed" << endl;
   }
   else
   {
      cout << "geometry shader compilation successful" << endl;
   }

   GLuint program = glCreateProgram();

   glProgramParameteriEXT(program, GL_GEOMETRY_INPUT_TYPE_EXT, GL_TRIANGLES);
   glProgramParameteriEXT(program, GL_GEOMETRY_OUTPUT_TYPE_EXT, GL_TRIANGLE_STRIP);
   glProgramParameteriEXT(program, GL_GEOMETRY_VERTICES_OUT_EXT, 3);

   glAttachShader(program, vertShader);
   glAttachShader(program, geomShader);
   glAttachShader(program, fragShader);

   glLinkProgram(program);

   GLint linkStatus;
   glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
   if (linkStatus == 1)
   { 
      cout << "all shaders linked" << endl;
   }

   glUseProgram(program);
   //glUseProgram(0);  //stop using program

   //place a value into a GPU register
   GLint loc = glGetUniformLocation(program, "image_1");
   //use texture unit 3 for one of the images
   glUniform1i(loc, 3);

   loc = glGetUniformLocation(program, "image_2");
   //use texture unit 1 for one of the images
   glUniform1i(loc, 1);

   delete[] str_v;
   delete[] str_f;
   delete[] str_g;
}
