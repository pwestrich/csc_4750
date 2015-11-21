#include "InstanceObject.h"
#include <GL/glut.h>

InstanceObject::InstanceObject(BasicObject* bo) : Node()
{
   obj = bo;
   obj->addRef();
   diffuse = new Color(0.3, 0.3, 1.0);
   shininess = 20;
}

InstanceObject::~InstanceObject()
{
   obj->removeRef();  //several ios can use the same bo, so delete is tricky
   delete diffuse;
}

void InstanceObject::buildTransform(Matrix* matrix)
{
   //multiple calls to this method will achieve the proper concatenation (later matrices are on the left)
   Matrix* temp = matrix->multiply(transform);
   delete transform;
   delete matrix;
   transform = temp;
}

void InstanceObject::render(Matrix* laterTransform)
{
   //laterTransform is just preceding instance transforms (Scene passes the identity matrix down)
   Matrix* updatedMatrix = laterTransform->multiply(transform);

   glPushMatrix();  //copy the current matrix to the top of the stack
   glPushAttrib(GL_CURRENT_BIT);  //saves OpenGL state information

   //get the instance transform and apply it
   //requires a column major matrix for OpenGL
   const float* updated_array = updatedMatrix->toArrayColumnMajor();
   glMultMatrixf(updated_array);  //multiply the matrix at the top of the stack by the new matrix

   GLfloat diffuse0[] = {static_cast<GLfloat>(diffuse->getRed()), static_cast<GLfloat>(diffuse->getGreen()), static_cast<GLfloat>(diffuse->getBlue()), 1.0}; //rgba
  
   //state machine settings
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse0);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

   obj->render();

   glPopAttrib();  //restores OpenGL state information
   glPopMatrix();

   delete[] updated_array;
   delete updatedMatrix;
}

void InstanceObject::setDiffuseMaterial(Color* mat)
{
   Color* temp = diffuse;
   diffuse = mat;
   delete temp;
}

void InstanceObject::setShininess(double shine)
{
   shininess = shine;
}
