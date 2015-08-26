#if !defined (AFFINETRANSFORMS_H)
#define AFFINETRANSFORMS_H

#include "Matrix.h"
using CSC2110::Matrix;

class AffineTransforms
{
   private:

   public:
      static Matrix* scale(double x, double y, double z);
};

#endif
