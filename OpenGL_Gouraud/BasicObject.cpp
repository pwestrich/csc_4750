#include "BasicObject.h"
#include "ReadObject.h"
#include <GL/glut.h>
#include <iostream>
using namespace std;

BasicObject::BasicObject(const char* file)
{
   vcount = numVertices(file);
   int fcount = numFaces(file);
   indexCount = fcount*3;

   vertices = getVertices(file, vcount);
   normals = getNormals(file, vcount);
   indices = getFaces(file, fcount);
}

BasicObject::~BasicObject()
{
   delete[] indices;
   delete[] vertices;
   delete[] normals;
}

void BasicObject::render()
{
   //need to create an array with the material colors for all vertices
   //float* colors = getColors(vcount, material->getRed(), material->getGreen(), material->getBlue());

   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_NORMAL_ARRAY);
   //glEnableClientState(GL_COLOR_ARRAY);

   glVertexPointer(3, GL_FLOAT, 0, vertices);
   glNormalPointer(GL_FLOAT, 0, normals);
   //glColorPointer(3, GL_FLOAT, 0, colors);

   //render
   glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, indices);
   //delete[] colors;
}
