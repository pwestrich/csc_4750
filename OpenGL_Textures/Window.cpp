#include <GL/glut.h>
#include "Window.h"
#include "Picture.h"

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
}
