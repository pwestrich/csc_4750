#include "BasicObject.h"
#include "ReadObject.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

BasicObject::BasicObject(const char* file)
{
   vcount = numVertices(file);
   int fcount = numFaces(file);
   indexCount = fcount*6;

   vertices = getVertices(file, vcount);
   normals = getNormals(file, vcount);

   indices = getFaces(file, fcount);
   for (int i = 0; i < 6*fcount; i+=6)
   {
	   //cout << indices[i] << " " << indices[i+1] << " " << indices[i+2] << " " << indices[i+3] << " " << indices[i+4] << " " << indices[i+5] <<endl;
   }
   //tex_coords = getTextureCoords(file, vcount);
}

BasicObject::~BasicObject()
{
   delete[] indices;
   delete[] vertices;
   delete[] normals;
   //delete[] tex_coords;
}

void BasicObject::render()
{
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_NORMAL_ARRAY);
   //glEnableClientState(GL_TEXTURE_COORD_ARRAY);

   glVertexPointer(3, GL_FLOAT, 0, vertices);
   glNormalPointer(GL_FLOAT, 0, normals);
   //glTexCoordPointer(2, GL_FLOAT, 0, tex_coords);

   //render (made a change here for adjacency)
   glDrawElements(GL_TRIANGLES_ADJACENCY_EXT, indexCount, GL_UNSIGNED_SHORT, indices);
}
