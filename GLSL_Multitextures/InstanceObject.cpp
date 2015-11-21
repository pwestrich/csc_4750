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
   int tex_num_1 = -1;
   int tex_num_2 = -1;
   texture_colors_1 = NULL;
   texture_colors_2 = NULL;
}

InstanceObject::~InstanceObject()
{
   obj->removeRef();  //several ios can use the same bo, so delete is tricky
   delete diffuse;
}

void InstanceObject::setDiffuseMaterial(Color* mat)
{
   if (texture_colors_1 != NULL)
   {
      delete[] texture_colors_1;
   }

   if (texture_colors_2 != NULL)
   {
      delete[] texture_colors_2;
   }

   Color* temp = diffuse;
   diffuse = mat;
   delete temp;
}

void InstanceObject::setColorTexture1(Texture* tex, int texNum)
{
   if (texture_colors_1 != NULL)
   {
      delete[] texture_colors_1;
   }

   tex_num_1 = texNum;
   texture_colors_1 = readTexture(tex);
   texture_width = tex->getWidth();  //power of two
   texture_height = tex->getHeight(); //power of two
}

void InstanceObject::setColorTexture2(Texture* tex, int texNum)
{
   if (texture_colors_2 != NULL)
   {
      delete[] texture_colors_2;
   }

   tex_num_2 = texNum;
   texture_colors_2 = readTexture(tex);
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

   if (texture_colors_1 != NULL)
   {
      glEnable(GL_TEXTURE_2D);
      glActiveTexture(GL_TEXTURE3);  //determines the texture unit that glBindTexture will assign the texture to
      glBindTexture(GL_TEXTURE_2D, tex_num_1); 

      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
      //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_colors_1);

      if (texture_colors_2 != NULL)
      {
         glActiveTexture(GL_TEXTURE1); //must be the same as the sampler2D variable assignment 

         //creates a texture object
         glBindTexture(GL_TEXTURE_2D, tex_num_2);  
         glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
         glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
         glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
         glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
         //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_colors_2);
      }

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
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

   obj->render();

   glPopAttrib();  //restores OpenGL state information
   glPopMatrix();

   delete[] updated_array;
   delete updatedMatrix;
   delete[] diffuse0;
}
