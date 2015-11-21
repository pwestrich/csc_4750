#include <iostream>
using namespace std;
#include <stdlib.h>

#include "Tokens.h"
using CSC2110::Tokens;
#include "ReadFile.h"
using CSC2110::ReadFile;

char* getText(const char* file_name)
{
   char* text = ReadFile::entireFile(file_name);
   cout << text << endl;
   return text;
}

float* getColors(int numVertices, float r, float g, float b)
{
   float* colors = new float[numVertices*3];

   for (int i = 0; i < numVertices*3; i += 3)
   {
      colors[i] = r;
      colors[i + 1] = g;
      colors[i + 2] = b;
   }

   return colors;
}

int numVertices(const char* ptr)
{
   int vcount = 0;
   string test;
   string* v = new string("v");
   ifstream infile(ptr);

   while (!infile.eof())
   {
      infile >> test;

      if (test == *v)  //counting number of vertices
      {
         vcount++;
      }
   }

   infile.close();
   delete v;

   return vcount;
}

int numFaces(const char* ptr)
{
   int fcount = 0;
   string test;
   string* f = new string("f");
   ifstream infile(ptr);

   while (!infile.eof())
   {
      infile >> test;

      if (test == *f)  //counting number of faces
      {
         fcount++;
      }
   }

   infile.close();
   delete f;
   return fcount;
}

float* getTextureCoords(const char* ptr, int vcount)
{
   float* texture = new float[vcount*2];

   float s, t;
   string test;
   string* vt = new string("vt");
   ifstream infile(ptr);
   vcount = 0;

   while (!infile.eof())
   {
      infile >> test;

      if (test == *vt)  //texture coordinates
      {
         infile >> s;
         infile >> t;
         texture[vcount] = s;
         texture[vcount + 1] = t;

         vcount = vcount + 2;
      }
   }

   infile.close();
   delete vt;
   return texture;
}

float* getNormals(const char* ptr, int vcount)
{
   float* normals = new float[vcount*3];

   float x, y, z;
   string test;
   string* vn = new string("vn");
   ifstream infile(ptr);
   vcount = 0;

   while (!infile.eof())
   {
      infile >> test;

      if (test == *vn)  //normals
      {
         infile >> x;
         infile >> y;
         infile >> z;

         normals[vcount] = x;
         normals[vcount + 1] = y;
         normals[vcount + 2] = z;

         vcount = vcount + 3;
      }
   }

   infile.close();
   delete vn;
   return normals;
}

float* getVertices(const char* ptr, int vcount)
{
   float* vertices = new float[vcount*3];

   float x, y, z;
   string test;
   string* v = new string("v");
   ifstream infile(ptr);
   vcount = 0;

   while (!infile.eof())
   {
      infile >> test;

      if (test == *v)  //vertices
      {
         infile >> x;
         infile >> y;
         infile >> z;

         vertices[vcount] = x;
         vertices[vcount + 1] = y;
         vertices[vcount + 2] = z;

         vcount = vcount + 3;
      }
   }

   infile.close();

   delete v;
   return vertices;
}

unsigned short* getFaces(const char* file_name, int fcount)
{
   int val = fcount*6;
   unsigned short* indices = new unsigned short[val];    //assume each face requires 3 vertices to define it

   String* f = new String("f");
   ReadFile* rf = new ReadFile(file_name);

   fcount = 0;
   String* test = rf->readLine();
   while (!rf->eof())
   {
	  Tokens tokens(test, ' ');
	  String* first_token = tokens.getToken(0);
	  
	  if (first_token->compare(f) == 0)
	  {
		  for (int i = 1; i < tokens.getNumTokens(); i++)
		  {
			  String* index = tokens.getToken(i);
			  indices[fcount] = atoi(index->getText()) - 1;
			  delete index;
			  fcount++;
		  }
	  }
		delete test;
		delete first_token;
		test = rf->readLine();
   }
   
   rf->close();
   delete rf;
   delete f;
   return indices;
}
