#include "Picture.h"
#include "Scene.h"
#include <GL/glut.h>

void Picture::render(int w, int h)
{
   //picture will not look exactly like in class programs
   //normals used are those from the text file

   GLuint* tex_num = new GLuint[2];
   glGenTextures(2, tex_num);

   const char* fileName = "sphere_texture.txt";
   BasicObject* sphere = new BasicObject(fileName);

   const char* texture = "MoonColor.raw";
   Texture* moon_color = new Texture(texture, 512, 256);
   const char* normal = "MoonNormal.raw";
   Texture* moon_normal = new Texture(normal, 512, 256);

   InstanceObject* sphere1 = new InstanceObject(sphere);
   Color* d1 = new Color(0.3, 0.3, 0.9);
   sphere1->setDiffuseMaterial(d1);
   sphere1->setColorTexture1(moon_color, tex_num[1]);
   sphere1->setColorTexture2(moon_normal, tex_num[0]);

   InstanceObject* sphere2 = new InstanceObject(sphere);
   Color* d2 = new Color(1.0, 0.0, 0.0);
   sphere2->setDiffuseMaterial(d2);
   sphere2->setColorTexture1(moon_normal, tex_num[0]);
   sphere2->setColorTexture2(moon_color, tex_num[1]);

   Scene* scene = new Scene();

   TransformNode* tn = new TransformNode();
   tn->buildTransform(AffineTransforms::scale(.9, .3, .3));
   tn->buildTransform(AffineTransforms::rotateX(90));
   tn->buildTransform(AffineTransforms::rotateY(290));
   tn->buildTransform(AffineTransforms::translate(0, 0, 0));
   tn->addChild(sphere1);

   scene->addTransformNode(tn);

   tn = new TransformNode();
   tn->buildTransform(AffineTransforms::scale(.7, 1.3, .7));
   tn->buildTransform(AffineTransforms::rotateX(90));
   tn->buildTransform(AffineTransforms::rotateZ(290));
   tn->buildTransform(AffineTransforms::translate(-.75, .75, 0));
   tn->addChild(sphere2);

   scene->addTransformNode(tn);

   scene->render(w, h);
   delete scene;
}
