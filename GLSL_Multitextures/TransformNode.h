#if !defined (TRANSFORMNODE_H)
#define TRANSFORMNODE_H

#include "Node.h"
#include "ListArray.h"
using CSC2110::ListArray;

class TransformNode : public Node
{
   private:
      ListArray<Node>* children;
      int sze;

   public:
      TransformNode();
      virtual ~TransformNode();
      void addChild(Node* child);
      void buildTransform(Matrix* matrix);
      void render(Matrix* laterTransform);
      Node* getNode(int index);
};

#endif
