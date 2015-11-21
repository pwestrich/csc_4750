#include "InstanceObject.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
using namespace std;

InstanceObject::InstanceObject(BasicObject* bo) : Node()
{
   obj = bo;
   obj->addRef();
   diffuse = new Color(0.3, 0.3, 1.0);
   shininess = 20;
   int tex_num = -1;
   texture_colors = NULL;
}

InstanceObject::~InstanceObject()
{
   obj->removeRef();  //several ios can use the same bo, so delete is tricky
   delete diffuse;
}

void InstanceObject::setDiffuseMaterial(Color* mat)
{
   if (texture_colors != NULL)
   {
      delete[] texture_colors;
   }

   Color* temp = diffuse;
   diffuse = mat;
   delete temp;
}

void InstanceObject::setColorTexture(Texture* tex, int texNum)
{
   if (texture_colors != NULL)
   {
      delete[] texture_colors;
   }

   tex_num = texNum;
   texture_colors = readTexture(tex);
   texture_width = tex->getWidth();  //power of two
   texture_height = tex->getHeight(); //power of two
}

void InstanceObject::setShininess(double shine)
{
   shininess = shine;
}

void InstanceObject::buildTransform(Matrix* matrix)
{
   //multiple calls to this method will achieve the proper concatenation (later matrices are on the left)
   Matrix* temp = matrix->multiply(transform);
   delete transform;
   delete matrix;
   transform = temp;
}

unsigned char* InstanceObject::readTexture(Texture* tex)
{
   int width = tex->getWidth();
   int height = tex->getHeight();
   int numColors = width*height*3;
   const char* textureFile = tex->getFileName();

   unsigned char* textureColors = new unsigned char[numColors];  
   ifstream infile(textureFile, ios::binary);   
   infile.read((char*)textureColors, numColors);
   infile.close();

   return textureColors;
}

void InstanceObject::render(Matrix* laterTransform)
{
   Matrix* updatedMatrix = laterTransform->multiply(transform);
   GLfloat* diffuse0 = new GLfloat[4];

   //probably should move the texture "setup" code elsewhere
   if (texture_colors != NULL)
   {
	   //enables texture mapping
       glEnable(GL_TEXTURE_2D);
	  //below we are creating a texture object which we will assign to a texture unit
	  //texture units pass their outputs on to other texture units for multitexturing
	  //you can apply texture coordinate transformations to texture units

      glBindTexture(GL_TEXTURE_2D, tex_num); //bind one of the integers as the current texture
	  //the following calls operate on the current texture (the one we just bound)
	  //to get OpenGL to do work on the texture later, simply rebind to the correct tex_num
      
	  //the texture should be "tiled"
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	  
	  //the current texture will use bilinear interpolation to determine the color (rather than point sampling)
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  //vs. GL_NEAREST
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);  //mipmap
	  
	  //mipmapping requires the specification of the various pre-averaged images
	  //can use the following glu function to automatically generate the mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, texture_width, texture_height, GL_RGB, GL_UNSIGNED_BYTE, texture_colors);
	  
	  //the surface color is multiplied by the texture color
	  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	  
	  //tells OpenGL where to find the actual texture data
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_colors);

	  
	 
	  /*
	  //specifying two texture units
      glActiveTexture(GL_TEXTURE0);  //determines the texture unit that glBindTexture will assign the texture to
	 
	  glBindTexture(GL_TEXTURE_2D, tex_num);
	  glClientActiveTexture(GL_TEXTURE0)
	  
      glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	 
	  glActiveTexture(GL_TEXTURE1);  //determines the texture unit that glBindTexture will assign the texture to
	  glBindTexture(GL_TEXTURE_2D, tex_num);
	  
	  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	  */

	  //the material color should be white for modulation
      diffuse0[0] = 1.0;
      diffuse0[1] = 1.0;
      diffuse0[2] = 1.0;
      diffuse0[3] = 1.0;
   }
   else
   {
      glDisable(GL_TEXTURE_2D);
      diffuse0[0] = diffuse->getRed();
      diffuse0[1] = diffuse->getGreen();
      diffuse0[2] = diffuse->getBlue();
      diffuse0[3] = 1.0;
   }

   glPushMatrix();
   glPushAttrib(GL_CURRENT_BIT);  //saves OpenGL state information

   //get the instance transform and apply it
   //requires a column major matrix for OpenGL
   const float* updated_array = updatedMatrix->toArrayColumnMajor();
   glMultMatrixf(updated_array);
  
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse0);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);  //need both of these for a good modulation rendering

   obj->render();

   glPopAttrib();  //restores OpenGL state information
   glPopMatrix();

   delete[] updated_array;
   delete updatedMatrix;
   delete[] diffuse0;
}
