#ifndef READ_OBJECT_H
#define READ_OBJECT_H

   int numVertices(const char* fileName);
   int numFaces(const char* fileName);
   float* getVertices(const char* fileName, int vcount);
   float* getNormals(const char* fileName, int vcount);
   uint32_t* getFaces(const char* fileName, int fcount);
   float* getColors(int numVertices, float r, float g, float b);
   float* getTextureCoords(const char* fileName, int vcount);

#endif
