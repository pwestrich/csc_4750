#if !defined (PICTURE_H)
#define PICTURE_H

#include "Pixel.h"

class Picture
{
   public:
      static void render(Pixel* pixel);
      //static BasicObject* readObject(const char* fileName);
      //static InstanceObject* buildInstanceObject(const char* fileName, BasicObject* obj);

   private:
};

#endif
