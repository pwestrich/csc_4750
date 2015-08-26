#include "AffineTransforms.h"
#include <math.h>

Matrix* AffineTransforms::scale(double x, double y, double z)
{
   Matrix* S = new Matrix(4, 4);

   S->setElement(1,1,x);
   S->setElement(1,2,0);
   S->setElement(1,3,0);
   S->setElement(1,4,0);

   S->setElement(2,1,0);
   S->setElement(2,2,y);
   S->setElement(2,3,0);
   S->setElement(2,4,0);

   S->setElement(3,1,0);
   S->setElement(3,2,0);
   S->setElement(3,3,z);
   S->setElement(3,4,0);

   S->setElement(4,1,0);
   S->setElement(4,2,0);
   S->setElement(4,3,0);
   S->setElement(4,4,1);

   return S;
}


