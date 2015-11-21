#if !defined (INSTANCEOBJECT_H)
#define INSTANCEOBJECT_H

#include "Node.h"
#include "BasicObject.h"

class InstanceObject : public Node
{
   private:
      BasicObject* obj;
      Color* diffuse;
      float shininess;

   public:
      InstanceObject(BasicObject* bo);
      virtual ~InstanceObject();
      void setDiffuseMaterial(Color* mat);
      void setShininess(double shine);
      void buildTransform(Matrix* matrix);
      void render(Matrix* laterTransform);
};

#endif
