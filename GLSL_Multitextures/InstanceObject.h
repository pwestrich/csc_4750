#if !defined (INSTANCEOBJECT_H)
#define INSTANCEOBJECT_H

#include "BasicObject.h"
#include "Node.h"
#include "Texture.h"

class InstanceObject : public Node
{
   private:
      BasicObject* obj;
      Color* diffuse;
      float shininess;

      unsigned char* texture_colors_1;
      unsigned char* texture_colors_2;
      int texture_width;
      int texture_height;
      int tex_num_1;
      int tex_num_2;

   public:
      InstanceObject(BasicObject* bo);
      virtual ~InstanceObject();
      void setDiffuseMaterial(Color* mat);
      void setShininess(double shine);
      void buildTransform(Matrix* matrix);
      void render(Matrix* laterTransform);
      void setColorTexture1(Texture* tex, int tex_num);
      void setColorTexture2(Texture* tex, int tex_num);

      static unsigned char* readTexture(Texture* tex);
};

#endif
