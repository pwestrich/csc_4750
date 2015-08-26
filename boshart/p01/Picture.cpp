#include "Picture.h"
#include "Color.h"

void Picture::render(Pixel* pix)
{
    //draw a red square
    Color color = Color(1, 0, 0);   
    for (int i = 0; i < 200; i++)
    {
       for (int j = 0; j < 200; j++)
       {
          pix->drawPixel(i, j, color);
       }
    }
}

/*
int getFaceIndex(String* face_indices)
{
   ArrayListIterator<String>* sub = face_indices->tokenize('/');
   String* face_index = sub->next();
   int index = face_index->parseInteger();
   delete face_index;
   //the rest of the tokens are not used, but need to be deleted
   while(sub->hasNext())
   {
      String* temp = sub->next();
      delete temp;
   }
   delete sub;
   return index;
}

BasicObject* Picture::readObject(const char* fileName)
{
   BasicObject* obj = new BasicObject();
   FileIO* file = new FileIO(fileName, ' '); //assumed to be a read if a delimiter is specified

   ArrayList<Vertex> vertices;
   double x, y, z;
   String* v = new String("v");
   String* f = new String("f");

   while (!file->eof())
   {
      ArrayListIterator<String>* iter = file->getTokens();
      String* token = iter->next();

      //all vertices are held in the vertices list so that the faces can be created
      if (token->compare(v) == 0)  //vertices
      {
         delete token;

         token = iter->next();
         x = token->parseFloat();
         delete token;

         token = iter->next();
         y = token->parseFloat();
         delete token;

         token = iter->next();
         z = token->parseFloat();
         delete token;

         Vertex* vertex = new Vertex(x, y, z);
         vertices.add(vertex);
         obj->addVertex(vertex);
      }

      else if (token->compare(f) == 0)  //face definition
      {
         delete token;

         String* face_indices = iter->next();
         int index1 = getFaceIndex(face_indices);
         delete face_indices;
         face_indices = iter->next();
         int index2 = getFaceIndex(face_indices);
         delete face_indices;
         face_indices = iter->next();
         int index3 = getFaceIndex(face_indices);
         delete face_indices;

         Face* face = new Face();

         Vertex* vertex1 = vertices.get(index1);
         Vertex* vertex2 = vertices.get(index2);
         Vertex* vertex3 = vertices.get(index3);

         face->addVertex(vertex1);
         face->addVertex(vertex2);
         face->addVertex(vertex3);

         obj->addFace(face);
      }

      //still need to delete the tokens even if the line is completely disregarded
      else  
      {
         delete token;
         while(iter->hasNext())
         {
            token = iter->next();
            delete token;
         }
      }

      delete iter;
   }

   delete v;
   delete f;
   delete file;
   return obj;
}

InstanceObject* Picture::buildInstanceObject(const char* fileName, BasicObject* obj)
{
   InstanceObject* io = new InstanceObject(obj);
   FileIO* inputFile = new FileIO(fileName, 1);  //for reading

   //scale transformation
   String* line = inputFile->readLine();  //skip this line 
   delete line;
   line = inputFile->readLine();
   double sx = line->parseFloat();
   delete line;
   line = inputFile->readLine();
   double sy = line->parseFloat();
   delete line;
   line = inputFile->readLine();
   double sz = line->parseFloat();
   delete line;
   Matrix* scale = AffineTransforms::scale(sx, sy, sz);

   //rotation transformations
   line = inputFile->readLine();  //skip this line
   delete line;
   line = inputFile->readLine();
   double rx = line->parseFloat();
   delete line;
   Matrix* rotX = AffineTransforms::rotateX(rx);
   line = inputFile->readLine();
   double ry = line->parseFloat();
   delete line;
   Matrix* rotY = AffineTransforms::rotateY(ry);
   line = inputFile->readLine();
   double rz = line->parseFloat();
   delete line;
   Matrix* rotZ = AffineTransforms::rotateZ(rz);

   //translation transformation
   line = inputFile->readLine();  //skip this line
   delete line;
   line = inputFile->readLine();
   double tx = line->parseFloat();
   delete line;
   line = inputFile->readLine();
   double ty = line->parseFloat();
   delete line;
   line = inputFile->readLine();
   double tz = line->parseFloat();
   delete line;
   Matrix* translate = AffineTransforms::translate(tx, ty, tz);

   //standard TRS form
   io->buildTransform(scale);  //deletes the matrix when done
   io->buildTransform(rotX);  
   io->buildTransform(rotY);  
   io->buildTransform(rotZ); 
   io->buildTransform(translate); 

   delete inputFile;
   return io;
}
*/
